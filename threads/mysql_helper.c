#include <stdio.h>
#include <mysql.h>

#include "mysql_helper.h"

char *server   = "localhost";
char *user     = "root";
char *password = "";
char *database = "crawler";

struct connections *m_con_arr = NULL;

MYSQL *mysql_connect()
{
	MYSQL *conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, server, user, password, database, 3306, NULL, 0)) {
    	fprintf(stderr, "MYSQL hatasi: %s\n", mysql_error(conn));
    	return NULL;
	}

	return conn;
}