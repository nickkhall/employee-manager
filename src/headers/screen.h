#ifndef SCREEN_H
#define SCREEN_H

#include <ncurses.h>

#include "employee.h"
#include "window.h"
#include "menu.h"

extern const char SEARCH_LABEL[];
extern const char* CREATE_LABELS[];

// print_word
// Prints a word to the screen with a given x and y axis
void screen_print_word(WINDOW* win, const int y, const int x, const char* word);

// print_border
// Prints the border to the screen
void screen_print_border(Window* win);

// print_line
// Prints a horizonal line at a given y position
void screen_print_line(WINDOW* win, const int y);

// print_employee_headers
// Prints the Employee table header columns
void screen_print_employee_headers(WINDOW* win);

void screen_print_employee_row_none(WINDOW* win, const int row);

// print_employee_row
// Prints the Employee table row with Employee data
void screen_print_employee_row(WINDOW* win, Employee* employee, const int row);

// print_employee
// Prints the entire Employees table to the screen
void screen_print_employee(WINDOW* win, Employee* employee);

// print_search_label
// Displays a given search label to the screen
void screen_print_search_label(WINDOW* win);

// print_title
// Prints the Employee Manager title to the screen
void screen_print_title(WINDOW* window);

// print_menu
// Prints a menu to the screen
void screen_print_menu(WINDOW* win, Menu* menu, int menu_items_size);

void screen_print_form_labels(WINDOW* win, char** labels);

void screen_print_form_labels_create(WINDOW* win);

// RENDER
void screen_render_main_window(WINDOW* win);

void screen_render_menu_window(WINDOW* win);

void screen_render_render_window(WINDOW* win);

#endif

