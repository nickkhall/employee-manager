#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <form.h>
#include <ctype.h>

#include "headers/forms.h"
#include "headers/input.h"
#include "headers/window.h"
#include "headers/utils.h"

char* input_get_search_input(WINDOW* win) {
  int y_max = 0;
  int x_max = 0;
  getmaxyx(win, y_max, x_max);
  // enable cursor and output
  curs_set(1);
  echo();

  // temp buffer for user input
  // (ncurses `mvngetnstr` sanitizes so no buffer overflow)
  char* buffer = (char*) malloc(sizeof(char) * 101);
  if (!buffer || buffer == NULL) {
    printf("ERROR:: Failed to alloctate memory for buffer in input_get_search_input\n");
    free((char*) buffer);
    exit(1);
  }

  // get label for search (max 100 chars)
  mvwgetnstr(
      win,
      y_max / 2,
      x_max / 2,
      buffer,
      101
    );

  // disable cursor and output
  curs_set(0);
  noecho();

  // clear screen again
  window_clear(win);

  return buffer;
}


void input_handle_input(WINDOW* win, FORM* create_form, int* key) { 
  *key = wgetch(win);

  while(*key != 10) {
    switch(*key) {
      // tab character
      case 9:
      case KEY_DOWN:
          // go to next field
          form_driver(create_form, REQ_NEXT_FIELD);
          // go to end of the current buffer
          //form_driver(create_form, REQ_END_LINE);
          break;
        case KEY_UP:
          // go to previous field
          form_driver(create_form, REQ_PREV_FIELD);
          // go to end of the current buffer
          form_driver(create_form, REQ_END_LINE);
          break;
        case KEY_BACKSPACE:
          // delete the previous character
          form_driver(create_form, REQ_DEL_PREV);
          break;
        // space character
        case 32:          
          // inserts blank character at current position
          form_driver(create_form, REQ_INS_CHAR);
          // go to next character
          form_driver(create_form, REQ_NEXT_CHAR); 
          break;
        default:
          // print character
          form_driver(create_form, *key);
          break;
    }

    form_driver(create_form, REQ_VALIDATION);
    window_refresh(win);

    *key = wgetch(win);
  }
  
  window_refresh(win);
}

/*
 * ----------------------------------------------------
 * function: input_get_form_input
 *
 * Handles retrieving input from user in a form view.
 * ----------------------------------------------------
 * params  :
 *           > win      - pointer to Window struct
 *           > data     - data array of strings
 * ----------------------------------------------------
 * returns : data array of strings
 * ----------------------------------------------------
 */
char** input_get_form_input(WINDOW* win, char** data) {
  int y_offset = 0;
  int x_offset = 0;
  getmaxyx(win, y_offset, x_offset);

  y_offset = y_offset / 15;
  x_offset = x_offset / 5;

  FIELD* fields[11];
  FORM*  create_form;
  int key; 
  int rows;
  int cols;

  for (int f = 0; f < 11; f++) {
    if (f == 10) {
      *(fields + f) = NULL;
      break;
    }
    // allocate memory for data array
    *(data + f) = (char*) malloc(sizeof(char) * 101);
    if (!*(data + f) || *(data + f) == NULL) {
      printf("ERROR:: Failed to allocate memory for data in input_get_form_input\n");
      free(data);
      exit(1);
    }

    // create fields
    *(fields + f) = new_field(1, 55,  // height and width
                              (f * y_offset),
                              2,      // start x
                              0, 10); // render entire field and amount of buffers

    set_field_buffer(*(fields + f), 0, *(data + f));

    field_opts_on(*(fields + f), O_ACTIVE | O_EDIT);
    field_opts_off(*(fields + f), O_AUTOSKIP);

    set_field_back(*(fields + f), A_UNDERLINE);
  }
    
  // create a new form and post it
  create_form = new_form(fields);

  scale_form(create_form, &rows, &cols);

  set_form_win(create_form, win);
  set_form_sub(create_form, win);

  // post form
  post_form(create_form);

  // disable output
  noecho();
  // enable cursor
  curs_set(1);

  // start at first input field
  form_driver(create_form, REQ_FIRST_FIELD);

  // monitor user input
  input_handle_input(win, create_form, &key);

  // once we get here, the user pressed "Enter"
  // parse the fields and retrieve the data
  for (int d = 0; d < 10; d++) {
    // if we are on the first two fields (first and last name)
    if (d < 2) {
      if (d == 1) {
        // get first and last name for concatenation
        char* first = field_buffer(*fields, 0); 
        char* last = field_buffer(*(fields + 1), 0);

        // trim whitespaces
        utils_trim_whitespaces(first);
        utils_trim_whitespaces(last);

        // copy first and last name into data array
        strcpy(*data, first);
        strcpy(*(data + 1), last);
        // finish loop after adding first and last name
        continue;
      }

      // skip first name
      continue;
    }

    // field data to data array
    char* cur_field = field_buffer(*(fields + d), 0);
    cur_field = utils_trim_whitespaces(cur_field);
    strcpy(*(data + d), cur_field);
  }

  window_clear(win);
  // un-post form and free the memory
  unpost_form(create_form);
  free_form(create_form);
  for (int f = 0; f < 10; f++) {
    free_field(*(fields + f));
  }

  // hide cursor
  curs_set(0);

  return data;
}

