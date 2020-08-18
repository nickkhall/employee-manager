#ifndef __EMP_MAN_EMPLOYEE_H__
#define __EMP_MAN_EMPLOYEE_H__

#include <libpq-fe.h>
#include <time.h>

extern const char* employee_labels_mini[];

typedef struct employee_t {
  char id[33];
  char first[51];
  char last[51];
  char email[101];
  char address[76];
  char phone[51];
  time_t start;
  char gender[7];
  char ethnicity[51];
  char title[51];
  int* salary;
} employee_t;

typedef struct list_node_t {
  void* data;
  struct list_node_t* next;
} list_node_t;

typedef struct list_t {
  struct list_node_t* head;
} list_t;

employee_t* employee_push(employee_t* employee, char** data);

employee_t* employee_populate(employee_t* employee, char** data);

employee_t* employee_update(employee_t* employee, const char** data);

employee_t* employee_remove(employee_t* employee, const char* id);

void employee_destroy(employee_t* employee);

employee_t* employee_convert(PGresult* res, const char* const* params, employee_t* employee);

#endif

