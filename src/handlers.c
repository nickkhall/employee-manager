#include <libpq-fe.h>
#include <stdlib.h>

#include "headers/handlers.h"

#include "headers/db.h"
#include "headers/employee.h"
#include "headers/input.h"
#include "headers/utils.h"
#include "headers/screen.h"
#include "headers/window.h"

Employee* handlers_get_id(WINDOW* win, Employee* employee) {
  // get user input
  const char* user_input = input_get_search_input(win);

  const char* const* query_params = &user_input;

  if (!query_params || query_params == NULL) {
    printf("ERROR: Failure to assign query_params from input_get_search_input in handlers_get_by_id\n");
    exit(1);
  }

  // query db with query params
  PGresult* res = NULL;
  res = db_query_by_id(res, query_params);

  // get employee(s) data
  employee = employee_convert(res, query_params, employee);
 
  return employee;
};

Employee* handlers_post(WINDOW* win, Employee* employee) {
  char** data = (char**) malloc(sizeof(char*) * 11);
  const char** user_input = input_get_form_input(win, data);

  const char* const* query_params = &user_input;
  if (!query_params || query_params == NULL) {
    printf("ERROR:: Failure to assign query_params for input_get_form_input in handlers_post\n");
    free(data);
    exit(1);
  }

  PGresult* res = NULL;
  res = db_query_post(res, query_params);

  employee = employee_convert(res, query_params, employee);
  
  return employee;
};

