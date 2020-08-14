#ifndef DB_H
#define DB_H

#include <libpq-fe.h>

#include "employee.h"

extern const char SEARCH_BY_ID_QUERY[];

PGresult* db_query(PGconn* conn,
                  PGresult* res,
                  const char* query,
                  const char* const* queryParams,
                  const int num_of_queries);

PGresult* db_query_by_id(PGresult* res, const char* const* query_params);

void db_clean_up(PGconn* conn, PGresult* res);

void db_disconnect(PGconn* conn);

#endif

