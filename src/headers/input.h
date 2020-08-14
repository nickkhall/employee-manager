#ifndef INPUT_H
#define INPUT_H

#include <form.h>

#include "window.h"

char* input_get_search_input(WINDOW* win);

void input_handle_input(WINDOW* win, FORM* form, int* key);

char** input_form_create(WINDOW* win, char** data);

#endif

