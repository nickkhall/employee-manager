#include <string.h>
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#include "headers/menu.h"
#include "headers/window.h"
#include "headers/screen.h"
#include "headers/handlers.h"

char* main_menu_items[] = {
  "  Search  Employee  " ,
  "  Create  Employee  ",
  "  Update  Employee  ",
  "  Remove  Employee  ",
  "       Quit         "
};

Menu* menu_create(char** menu_items, const int menu_items_size) {
  Menu* main_menu = (Menu*) malloc(sizeof(Menu));
  if (!main_menu || main_menu == NULL) {
    printf("ERROR::Failure to allocate memory for main in menu_create\n");
    free(main_menu);
    // @TODO: Create global clean_up function solution for all memory if failure
    exit(1);
  }

  // set default main menu states
  main_menu->highlighted = 0;
  main_menu->state = 0;
  main_menu->items = (char**) malloc(sizeof(char*) * menu_items_size);
  if (!main_menu->items || main_menu->items == NULL) {
    printf("ERROR:: Failed to allocate memory for menu items in menu_create");
    free(main_menu->items);
    exit(1);
  }

  for (int m = 0; m < menu_items_size; m++) {
    *(main_menu->items + m) = (char*) malloc(sizeof(char) * strlen(*(menu_items + m)));
    strcpy(*(main_menu->items + m), *(menu_items + m));
  }

  return main_menu;
}

Menu* menu_create_main_menu() {
  Menu* menu = menu_create(main_menu_items, 5);
  if (!menu || menu == NULL) {
    printf("ERROR:: Failed to assign menu from menu_create in menu_create_main_menu\n");
    free(menu);
    exit(1);
  }

  return menu;
}

// menu_update
// Updates the menu states for state and highlighted
void menu_update(Menu* menu, int key_code, int items_size) {
  switch(key_code) {
    case 74:
    case 106:
    case KEY_DOWN:
      // Prevent the user from selecting item above the list
      if (menu->highlighted + 1 < items_size) {
        menu->highlighted += 1;
      }
      break;
    case 75:
    case 107:
    case KEY_UP:
      // Prevent user from selecting item below the list
      if (menu->highlighted - 1 > -1) {
        menu->highlighted -= 1;
      }
      break;
    default:
      break;
    };

  menu->state = menu->highlighted + 1;
};

// menu_handle_search
void menu_handle_search(WINDOW* win) {
  screen_print_search_label(win);

  Employee* employee = NULL;
  employee = handlers_get_id(win, employee); 

  // print employee data to screen
  screen_print_employee(win, employee);

  // wait for user to press "Escape"
  // @TODO: make me into function
  noecho();
  int key = 0;
  if ((key = wgetch(win)) != ERR) {
    while(key != 27) {
      key = wgetch(win);
    }
  }

  employee_destroy(employee);

  window_clear(win);
}

void menu_handle_create(WINDOW* win) {
  Employee* employee = NULL;
  employee = handlers_post(win, employee);
}
