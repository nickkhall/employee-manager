#ifndef MENU_H
#define MENU_H

#include "window.h"

extern char* main_menu_items[];

typedef struct m {
  short int highlighted;
  short int state;
  char** items;
} Menu;

Menu* menu_create(char** menu_items, const int menu_items_size);

Menu* menu_create_main_menu();

void menu_update(Menu* menu, int key_code, int items_size);

void menu_destroy(Menu* menu);

void menu_handle_search(WINDOW* win);

void menu_handle_create(WINDOW* win);

void menu_handle_update();

void menu_handle_remove();
#endif
