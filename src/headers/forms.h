#ifndef FORMS_H
#define FORMS_H

#include <form.h>

FORM* forms_create_form(FIELD** fields);

FORM* forms_populate_fields(FORM* form,
														FIELD** fields,
														char** data,
														int* y_offset,
														int* x_offset);

int forms_destroy_form(FORM* form);

#endif

