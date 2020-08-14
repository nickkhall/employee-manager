#include <ncurses.h>
#include <stdlib.h>

#include "headers/window.h"

void window_refresh(WINDOW* win) {
  wrefresh(win);
};

Window* window_initialize_windows(Window* win) {
  initscr();
  noecho();
  curs_set(0);

  // create Window struct
  win = (Window*) malloc(sizeof(Window));
  if (!win || win == NULL) {
    printf("ERROR:: Failed to allocate memory for Window* win in window_initialize_windows\n");
    free(win);
    exit(1);
  }

  getmaxyx(stdscr, win->y_max, win->x_max);

  // assign new window instance to Window struct
  win->main_window = newwin(0,0,0,0);

  win->menu_window = derwin(win->main_window,
                            win->y_max - 17,
                            (win->x_max / 5),
                            2,
                            2);

  win->render_window = derwin(win->main_window,
                              win->y_max - 17,
                              (win->x_max) - (win->x_max / 5) - 4,
                              2,
                              (win->x_max / 5) + 2);

  win->stats_window = derwin(win->main_window,
                             14,
                             win->x_max - 4,
                             win->y_max - 15,
                             2);

  box(win->menu_window, 0, 0);
  box(win->render_window, 0, 0);
  box(win->stats_window, 0, 0);

  keypad(win->menu_window, true);
  keypad(win->render_window, true);

  scrollok(win->render_window, true);
  scrollok(win->stats_window, true);

  window_refresh(win->main_window);
  window_refresh(win->menu_window);
  window_refresh(win->render_window);
  window_refresh(win->stats_window);

  return win;
};

void window_print_to_window(WINDOW* win, int y, int x, char* word) {
  mvwprintw(win, y, x, word);
};

void window_clear(WINDOW* win) {
  wclear(win);

  window_refresh(win);
};

void window_destroy(Window* win) {
  curs_set(1);
  echo();

  endwin();
  free(win);
  system("reset");
}

