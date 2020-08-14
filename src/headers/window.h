#ifndef WINDOW_H
#define WINDOW_H

#include <ncurses.h>

typedef struct {
  unsigned int y_max;
  unsigned int x_max;

  WINDOW* main_window;
  WINDOW* menu_window;
  WINDOW* render_window;
  WINDOW* stats_window;
} Window;

Window* window_initialize_windows(Window* win);

void window_print_to_window(WINDOW* win, int y, int x, char* word);

void window_refresh(WINDOW* win);

void window_clear(WINDOW* win);

void window_destroy(Window* win);

#endif

