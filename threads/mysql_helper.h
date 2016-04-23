#ifndef _MYSQLHELPER_H_
#define _MYSQLHELPER_H_

#include <mysql.h>

#include "uthash.h"

struct connections {
	int tid;                   /* key */
    MYSQL *conn;
    UT_hash_handle hh;         /* makes this structure hashable */
};

// An array to hold all MySQL connections used by threads
struct connections *m_con_arr;

// MySQL connection paramters
char *server  ;
char *user    ;
char *password;
char *database;

MYSQL *conn;

/**
 * @function mysql_connect
 * @brief Connects to a MySQL server.
 * 
 * @return a newly created MySQL connection.
 */
MYSQL *mysql_connect();

#endif /* _MYSQLHELPER_H_ */
