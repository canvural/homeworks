#include <stdio.h>
#include <mysql.h>

#include "mysql_helper.h"

int main()
{
	conn = mysql_connect();

	char query[255] = "INSERT INTO test (title) VALUES('denemeeeeeeee')";

	int i = 0;

	for(i = 0; i < 256; i++) {
		if (mysql_query(conn, query)) {
	        fprintf(stderr, "%s\n", mysql_error(conn));
	        exit(1);
	    }
	}

	return 0;
}