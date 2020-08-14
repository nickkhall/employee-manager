#include <stdlib.h>
#include <stdio.h>
#include <libpq-fe.h>

#include "headers/employee.h"
#include "headers/utils.h"

const char* employee_labels_mini[] = {
  "Name",     // 1 / 2
  "Email",    // 3
  "Address",  // 4
  "Phone",    // 6
  "Title"     // 9
};

/*
 * ----------------------------------------------
 * function: employee_push
 * ----------------------------------------------
 * Creates or adds to a linked list of Employees.
 * ----------------------------------------------
 */
Employee* employee_push(Employee* employee_head, char** data) {
  if (employee_head == NULL) {
    employee_head = (Employee*) malloc(sizeof(Employee));

    employee_populate(employee_head, data);
    employee_head->next_employee = NULL;
  } else {
    Employee* head = NULL;
    head = (Employee*) malloc(sizeof(Employee));
    if (!head || head == NULL) {
      printf("ERROR:: Failure to allocate memory for employee head in employee_push\n");
      free(head);
      free(employee_head);
      exit(1);
    }

    employee_populate(head, data);
    employee_head->next_employee = NULL;

    head->next_employee = employee_head;
    employee_head = head;
  }

  return employee_head;
};

/*
 * -------------------------------------
 * function: employee_populate
 * -------------------------------------
 * Allocates memory for Employee struct, 
 * and assigns it data.
 * -------------------------------------
 */
Employee* employee_populate(Employee* employee, char** data) {
  // allocate memory for employee data
  employee->id        = (char*) malloc(sizeof(char) * 33);
  employee->first     = (char*) malloc(sizeof(char) * 51);
  employee->last      = (char*) malloc(sizeof(char) * 51);
  employee->email     = (char*) malloc(sizeof(char) * 76);
  employee->address   = (char*) malloc(sizeof(char) * 76);
  employee->phone     = (char*) malloc(sizeof(char) * 51);
  employee->start     = (time_t) malloc(sizeof(time_t));
  employee->gender    = (char*) malloc(sizeof(char) * 7);
  employee->ethnicity = (char*) malloc(sizeof(char) * 51);
  employee->title     = (char*) malloc(sizeof(char) * 51);
  employee->salary    = (int*) malloc(sizeof(int));

  int* salary = (int*) malloc(sizeof(int));
  if (!salary || salary == NULL) {
    printf("ERROR::Failure to allocate memory for salary in employee_populate.\n");
    free(salary);
    exit(1);
  }

  *salary = atoi(*(data + 10));
  // assign data to employee struct
  employee->id        = *(data);
  employee->first     = *(data + 1);
  employee->last      = *(data + 2);
  employee->email     = *(data + 3);
  employee->address   = *(data + 4);
  employee->phone     = *(data + 5);
  employee->start     = (time_t)(data + 6);
  employee->gender    = *(data + 7);
  employee->ethnicity = *(data + 8);
  employee->title     = *(data + 9);
  employee->salary    = salary;

  return employee;
}

/*
 * ----------------------------------
 * function: employee_update
 * ----------------------------------
 * Updates an Employee by a given ID.
 * ----------------------------------
 */



/*
 * ---------------------------------------------
 * function: employee_destroy
 * ---------------------------------------------
 * Destroys the entire linked list of Employees.
 * ---------------------------------------------
 */
void employee_destroy(Employee* employee) {
  while (employee != NULL) {
    free(employee);
    employee = employee->next_employee;
  }
}

/*
 * -----------------------------------------------------------------
 * function: employee_convert
 * -----------------------------------------------------------------
 * Handles querying database and returning linked list of Employees.
 * -----------------------------------------------------------------
 */
Employee* employee_convert(PGresult* res, const char* const* params, Employee* employee) {
  // if there are no parameters, error out, something went wrong
  if (!*(params)) {
    printf("ERROR:: Something went wrong. The query params passed were invalid.\n");
    exit(1);
  }

  if (PQresultStatus(res) != PGRES_TUPLES_OK) {
    printf("ERROR:: %s\n", PQresultErrorMessage(res));
    PQclear(res);

    return NULL;
  }
  
  // num of employees returned (row)
  const int rows = PQntuples(res);
  // num of data items in employee (column)
  const int cols = PQnfields(res);

  // allocate memory for employee data to be used to populate an employee struct
  char*** employee_data = NULL;
  employee_data = (char***) malloc((sizeof(char*) * rows));
  if (!employee_data || employee_data == NULL) {
    printf("ERROR:: Failed to allocate memory for employee_data in employee_convert\n");
    free(employee_data);
    exit(1);
  }
  
  // if there are no employees,
  // return null for soft fail
  if (rows < 1) {
    return NULL;
  }

  // else create data for employees
  for (int r = 0; r < rows; r++) {
    *(employee_data + r) = (char**) malloc(sizeof(char*) * cols);
    if (!*(employee_data + r) || *(employee_data + r) == NULL) {
      printf("ERROR:: Failed to allocate memory for employee_data array in employee_convert\n");
      employee_destroy(employee);
      exit(1);
    }

    // transfer Postgres response data to Employee struct(s)
    utils_convert_pq_res_data(*(employee_data + r), res, r);

    // create or add to employee linked list with current employee struct
    employee = employee_push(employee, *(employee_data + r));
  }

  PQclear(res);

  return employee;
}
