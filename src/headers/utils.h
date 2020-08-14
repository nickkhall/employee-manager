#ifndef UTILS_H
#define UTILS_H

#include <libpq-fe.h>

char** utils_convert_pq_res_data(char** data_pointer, PGresult* res, const int row);

char* utils_trim_whitespaces(char* str);

#endif

