#include <libpq-fe.h>
#include <stdlib.h>
#include <ncurses.h>

#include "src/headers/menu.h"
#include "src/headers/window.h"
#include "src/headers/app.h"

int main() {
  // create window
  Window* main_win = NULL;
  main_win = window_initialize_windows(main_win);
  if (!main_win || main_win == NULL) {
    free(main_win);
    return 1;
  }

  Menu* main_menu = NULL;
  main_menu = menu_create_main_menu();
  if (!main_menu || main_menu == NULL) {
    free(main_menu);
    return 1;
  }

  // run application
  while (main_menu->state > -1) {
    app(main_win, main_menu);
  }

  // destroy window
  window_destroy(main_win);
  free(main_menu);
  return 0;
}
