#ifndef __EMP_MAN_EMPLOYEE_H__
#define __EMP_MAN_EMPLOYEE_H__

#include <libpq-fe.h>
#include <time.h>

extern const char* employee_labels_mini[];

typedef struct Employee {
  char* id;
  char* first;
  char* last;
  char* email;
  char* address;
  char* phone;
  time_t start;
  char* gender;
  char* ethnicity;
  char* title;
  int* salary;
  struct Employee* next_employee;
} Employee;

typedef struct {
  struct Employee* head;
} Employees;

Employee* employee_push(Employee* employee, char** data);

Employee* employee_populate(Employee* employee, char** data);

Employee* employee_update(Employee* employee, const char** data);

Employee* employee_remove(Employee* employee, const char* id);

void employee_destroy(Employee* employee);

Employee* employee_convert(PGresult* res, const char* const* params, Employee* employee);

#endif

