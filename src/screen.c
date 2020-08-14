#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "headers/screen.h"

#include "headers/employee.h"
#include "headers/window.h"
#include "headers/menu.h"
#include "headers/utils.h"

const char SEARCH_LABEL[] = "Search by ID, First and/or Last name:";
const char* CREATE_LABELS[] = {
  "First*    : ",
  "Last*     : ",
  "Email*    : ",
  "Address   : ",
  "Phone     : ",
  "Start     : ",
  "Gender    : ",
  "Ethnicity : ",
  "Title*    : ",
  "Salary*   : "
};

void screen_print_word(WINDOW* win, const int y, const int x, const char* word) {
  mvwprintw(win, y, x, word);
  
  window_refresh(win);
}

void screen_print_line(WINDOW* win, const int y) {
  int y_max = 0;
  int x_max = 0;
  getmaxyx(win, y_max, x_max);

  // render a horizonal line for data separation
  char* screen_print_line = (char*) malloc((sizeof(char) * x_max) - 4);
  if (!screen_print_line || screen_print_line == NULL) exit(1); 
  for (int s = 0; s < x_max - 2; s++) {
    *(screen_print_line + s) = '-';
  }

  // print horizontal line
  screen_print_word(win,
                    ((y_max + 1) - y_max + 2),
                    y,
                    screen_print_line
  );

  // free screen line memory
  free(screen_print_line);
};

void screen_print_employee_headers(WINDOW* win) {
  int y_max = 0;
  int x_max = 0;
  getmaxyx(win, y_max, x_max);

  const unsigned long int word_offset = (x_max / 7);

  // keep track of current x axis offset for n value
  unsigned int offset = word_offset;

  // print the employee table header labels
  for (int l = 0; l < 5; l++) {
    const char* current_label = *(employee_labels_mini + l);
    const unsigned long int current_label_length = strlen(current_label);

    screen_print_word(win, 1, offset, current_label);

    // increase the x axis offset for next label
    offset += word_offset + (current_label_length / 2);
  }
};

void screen_print_employee_row_none(WINDOW* win, const int row) {
  int y_max = 0;
  int x_max = 0;
  getmaxyx(win, y_max, x_max);

  char no_employees_text[] = "No employees found.";

  screen_print_word(win,
                    row + 4,
                    (x_max / 2) - (strlen(no_employees_text) / 2),
                    no_employees_text); 
}

void screen_print_employee_row(WINDOW* win, Employee* employee, const int row) {
  int y_max = 0;
  int x_max = 0;
  getmaxyx(win, y_max, x_max);

  // allocate memory for first and last name string
  unsigned long int first_size = strlen(employee->first);
  unsigned long int last_size = strlen(employee->last);

  char* name = malloc(first_size + last_size);
  if (!name || name == NULL) {
    printf("ERROR::Failed to allocate memory for name in screen_print_employee_row\n");
    free(name);
    exit(1);
  }

  // generate string for first and last name
  strcpy(name, employee->first);
  strcat(name, " ");
  strcat(name, employee->last);

  char* temp_data[5] = {name,
                        employee->email,
                        employee->address,
                        employee->phone,
                        employee->title};

  // keep track of offset that labels should render apart from eachother (x axis)
  unsigned long int word_offset = (x_max / 7);

  // keep track of current x axis offset for n value
  unsigned int offset = (word_offset - strlen(*(temp_data)) / 2);

  for (int e = 0; e < 5; e++) {
    char * cur_value = *(temp_data + e);
    screen_print_word(win, (row + 4), offset, cur_value); 
    
    offset += word_offset + strlen(cur_value) / 2;
  }

  free(name);
};

void screen_print_employee(WINDOW* win, Employee* employee) {
  int y_max = 0;
  int x_max = 0;
  getmaxyx(win, y_max, x_max);

  int cur_row = 0;
  window_clear(win);
  box(win, 0, 0);

  screen_print_employee_headers(win);

  screen_print_line(win, 1);

  // if there were no employees found
  if (employee == NULL) {
    // print out no users found to table
    screen_print_employee_row_none(win, cur_row++);
    return;
  }

  // if we make it here, have employee data,
  // so print it to the screen
  while(employee != NULL) {
    // print employee row with employee data
    screen_print_employee_row(win, employee, cur_row++);
    // advance the list
    employee = employee->next_employee;
  }

  // print helper label text for returning to menu at bottom of screen
  char return_label[] = "Press \"Escape\" to return to the main menu";
  // print helper label at bottom of the screen
  screen_print_word(win,
            y_max - 5,
            (x_max / 2) - (strlen(return_label) / 2),
            return_label);
};

void screen_print_search_label(WINDOW* win) {
  int y_max = 0;
  int x_max = 0;
  getmaxyx(win, y_max, x_max);

  // get length of search form label
  int label_len = strlen(SEARCH_LABEL);

  // clear screen
  window_clear(win);
  box(win, 0, 0);

  // print search form label
  screen_print_word(
    win,
    y_max / 2,
    (x_max / 2) - label_len - 1,
    SEARCH_LABEL
  );

  window_refresh(win);
};

void screen_print_title(WINDOW* win) {
  int y_max = 0;
  int x_max = 0;
  getmaxyx(win, y_max, x_max);

  const char* header[] = {
    " ______                 _                         __  __",
    "|  ____|               | |                       |  \\/  |",
    "| |__   _ __ ___  _ __ | | ___  _   _  ___  ___  | \\  / | __ _ _ __   __ _  __ _  ___ _ __",
    "|  __| | '_ ` _ \\| '_ \\| |/ _ \\| | | |/ _ \\/ _ \\ | |\\/| |/ _` | '_ \\ / _` |/ _` |/ _ \\ '__|",
    "| |____| | | | | | |_) | | (_) | |_| |  __/  __/ | |  | | (_| | | | | (_| | (_| |  __/ |",
    "|______|_| |_| |_| .__/|_|\\___/ \\__, |\\___|\\___| |_|  |_|\\__,_|_| |_|\\__,_|\\__, |\\___|_|",
    "                 | |             __/ |                                      __/ |",
    "                 |_|            |___/                                      |___/"
  };

  for (short int i = 0; i < 8; i++) {
    screen_print_word(
      win,
      ((y_max / 2) + i) - 4,
      ((x_max / 2) - (91 / 2) + 2),
      *(header + i)
    );
  }

  box(win, 0, 0);
  window_refresh(win);
};

void screen_print_menu(WINDOW* win, Menu* menu, int menu_items_size) {
  int y_max = 0;
  int x_max = 0;
  getmaxyx(win, y_max, x_max);

  int key_code = 0;

  do {
    window_refresh(win);

    for (int i = 0; i < menu_items_size; i++) {
      if (i == menu->highlighted) {
        // reverse colors to denote highlight
        wattron(win, A_REVERSE);
      }

      screen_print_word(
        win,
        ((y_max / 2) + i) - 2,
        (x_max / 2) - (strlen(*(menu->items + i)) / 2),
        *(menu->items + i)
      );

      // Turn off reverse attribute
      wattroff(win, A_REVERSE);
    }

    // refresh window
    window_refresh(win);

    key_code = wgetch(win);

    // Update the menu with the currently selected item
    menu_update(menu, key_code, menu_items_size);
  } while (key_code != 27 && key_code != 10);

  // refresh window
  window_refresh(win);
}

void screen_print_form_labels_create(WINDOW* win) {
  int y_max = 0;
  int x_max = 0;
  getmaxyx(win, y_max, x_max);

  window_clear(win);
  box(win, 0, 0);
  int offset = (y_max / 11);

  for (int l = 0; l < 11; l++) {
    char* cur_label = *(CREATE_LABELS + l);

    screen_print_word(win, offset, x_max / 7, cur_label);
    if (l % 1 == 0) {
      offset++;
    }

    offset += (y_max / 11) - 1;
  }

  window_refresh(win);
}

