#ifndef HANDLERS_H
#define HANDLERS_H

#include "employee.h"
#include "window.h"

void handlers_get(const char* const* params);

Employee* handlers_get_id(WINDOW* win, Employee* employee);

Employee* handlers_post(WINDOW* win, Employee* employee);

void handlers_put(const char* const* params);

void handlers_delete(const char* const* params);

#endif

