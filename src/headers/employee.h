#ifndef __EMP_MAN_EMPLOYEE_H__
#define __EMP_MAN_EMPLOYEE_H__

#include <libpq-fe.h>
#include <time.h>

extern const char* employee_labels_mini[];

typedef struct {
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
} employee_t;

typedef struct {
  struct employee_t*      data;
  struct employee_list_node_t* next;
} employee_list_node_t;

typedef struct {
  struct employee_list_node_t* head;
} employee_list_t;

Employee* employee_push(Employee* employee, char** data);

Employee* employee_populate(Employee* employee, char** data);

Employee* employee_update(Employee* employee, const char** data);

Employee* employee_remove(Employee* employee, const char* id);

void employee_destroy(Employee* employee);

Employee* employee_convert(PGresult* res, const char* const* params, Employee* employee);

#endif

