#include <form.h>
#include <stdlib.h>

#include "headers/forms.h"

FORM* forms_create_form(FIELD** fields) {
  FORM* form = (FORM*) malloc(sizeof(FORM));

  form = new_form(fields);

  
}

FORM* forms_populate_fields(FORM* form,
                            FIELD** fields,
                            char** data,
                            int* y_offset,
                            int* x_offset)
{
  for (int f = 0; f < 11; f++) {
    if (f == 10) {
      *(fields + f) = NULL;
      break;
    }
    // allocate memory for data array
    *(data + f) = (char*) malloc(sizeof(char) * 101);
    if (!*(data + f) || *(data + f) == NULL) {
      printf("ERROR:: Failed to allocate memory for data in input_get_form_input\n");
      free(data);
      exit(1);
    }

    // create fields
    *(fields + f) = new_field(1, 50,             // height and width
                              (f * *(y_offset)), // start y
                              *x_offset,         // start x
                              0, 10);            // render 100% field & amount of buffers

    field_opts_off(*(fields + f), O_AUTOSKIP);
    // set field type with field validation
    set_field_back(*(fields + f), A_UNDERLINE);

    set_field_buffer(*(fields + f), f, *(data + f));
  }

  return form;
}

