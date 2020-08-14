#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <libpq-fe.h>

#include "headers/utils.h"
#include "headers/employee.h"

char** utils_convert_pq_res_data(char** data_pointer, PGresult* res, const int row) {
  for (int col = 0; col < 11; col++) {
    const char* current_pq = PQgetvalue(res, row, col);
    unsigned long int current_pq_length = strlen(current_pq);
    char* current_string = (char*) malloc(sizeof(char) * (current_pq_length + 1));

    strcpy(current_string, current_pq);
    *(data_pointer + col) = current_string;
 }

  return data_pointer;
};

char* utils_trim_whitespaces(char* str){
  char* end;
  
  // trim leading space
  while(isspace(*str))
  	str++;
  
  if(*str == 0) // all spaces?
  	return str;
  
  // trim trailing space
  end = str + strnlen(str, 101) - 1;
  
  while(end > str && isspace(*end))
  	end--;
  
  // write new null terminator
  *(end + 1) = '\0';
  
  return str;
}
