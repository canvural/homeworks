#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "sqlite3.h"

//#define DEBUG

// Our sql statement to create the table, if it not exists
#define TABLE "CREATE TABLE IF NOT EXISTS phonebook (id INTEGER PRIMARY KEY, name TEXT, surname TEXT, phone TEXT, m_phone TEXT, email TEXT, address TEXT, city TEXT, country TEXT)"

// Used for command line parsing
extern char *optarg;
extern int optind;
int c;

// User specified database file name
char *database_file;

// For holding the users choice from menu
int choice;

// Our database
sqlite3 *db;

sqlite3_stmt *res;

const char *tail;

// This will hold any error message
// when there is an error
char *sql_err = 0;

// One of the error codes returning from sqlite3_ functions
int rc;

// Operations
void ph_search();
void ph_add();
void ph_update();
void ph_delete();

static void usage()
{
	printf(" Usage: phonebook [-f database_file]\n");
	printf("\t-f : Database file name to be used for processing\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
	// Turn off getopt errors as we will handle it manually
	opterr = 0;

	// Our default database file name
	database_file = "phonebook.db";

	// Parse command line options
	while ((c = getopt(argc,argv,"f:")) != -1) {
		switch (c) {
		case 'f':
			database_file = optarg;
			break;
		case '?':
		case ':':
            if (optopt == 'f')
            	fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isprint (optopt))
            	fprintf (stderr, "Unknown option '-%c'.\n", optopt);
            else
            	fprintf (stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
            usage();
		default:
			usage();
		}
	}

#ifdef DEBUG
	printf("Your database file name: %s\n", database_file);
#endif

	// Open the database
	rc = sqlite3_open(database_file, &db);
	if(SQLITE_OK != rc){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return(1);
	}

	// Create our table if its not already created
	rc = sqlite3_exec(db, TABLE, NULL, NULL, &sql_err);
	if(SQLITE_OK != rc){
	 	fprintf(stderr, "SQL error: %s\n", sql_err);
	 	sqlite3_free(sql_err);
	 	return 1;
	}

	// MAIN MENU
	printf(""
	"\n*************************\n"
	  "**      PhoneBook      **\n"
	  "**                     **\n"
	  "**  1) Search          **\n"
	  "**  2) Add             **\n"
	  "**  3) Update          **\n"
	  "**  4) Delete          **\n"
	  "**  5) Quit            **\n"
	  "*************************\n"
	  ""  
	"\n");

	// Ask user to enter a number
	// until user enters number between 0 and 6
	do {
		printf("Enter your choice: ");
		if(!scanf("%d", &choice)) {choice = 0; while(getchar() != '\n');}
	} while(choice <= 0 || choice >= 6);

#ifdef DEBUG
	printf("You choosed: %d\n", choice);
#endif

	switch(choice) {
		case 1:
			ph_search();
			break;
		case 2:
			ph_add();
			break;
		case 3:
			ph_update();
			break;
		case 4:
			ph_delete();
			break;
		case 5:
			printf("Goodbye!");
			return 1;
			break;
		default:
			// TODO: ?
			break;
	}

	// Cleanup
	sqlite3_close(db);

	return 0;
}

// Search database by criteria which taken from user
void ph_search(){
	int _criteria = 0;
// Start label
start:
	printf(""
	"\n*************************\n"
	  "**   Search Criteria   **\n"
	  "**                     **\n"
	  "**  1) Name            **\n"
	  "**  2) Surname         **\n"
	  "**  3) Phone           **\n"
	  "**  4) Mobile Phone    **\n"
	  "**  5) Email           **\n"
	  "**  6) Address         **\n"
	  "**  7) City            **\n"
	  "**  8) Country         **\n"
	  "**  9) Quit            **\n"
	  "*************************\n"
	  ""  
	"");

	// Ask user to enter a number
	// until user enters number between 0 and 10
	do {
		printf("Enter your choice: ");
		if(!scanf("%d", &_criteria)) {
			_criteria = 0;
			// Dirty way to clear scanf's internal buffer
			// I should have used fgets :)
			while(getchar() != '\n');
		}
	} while(_criteria <= 0 || _criteria >= 10);

	char *column;

	switch(_criteria) {
		case 1:
			column = "name";
			break;
		case 2:
			column = "surname";
			break;
		case 3:
			column = "phone";
			break;
		case 4:
			column = "m_phone";
			break;
		case 5:
			column = "email";
			break;
		case 6:
			column = "address";
			break;
		case 7:
			column = "city";
			break;
		case 8:
			column = "country";
			break;
		default:
			break;
	}

	char criteria[255];

	printf("Enter your criteria: ");
	scanf("%254s", criteria);
	while(getchar() != '\n');

	// String to hold our SQL statement
	char sql[255] = "\0";

	snprintf(sql, 254, "SELECT * FROM phonebook WHERE %s LIKE \'%%%s%%\'", column, criteria);

#ifdef DEBUG
	printf("SQL Statement: %s\n", sql);
#endif

	// Prepare the statement
	rc = sqlite3_prepare_v2(db, sql, 255, &res, &tail);
	if(SQLITE_OK != rc){
	 	fprintf(stderr, "SQL error: %s\n", sql_err);
	 	sqlite3_free(sql_err);
	 	exit(EXIT_FAILURE);
	}

#ifdef DEBUG
	int _status = -1;
	while (_status != SQLITE_DONE) {
        _status = sqlite3_step(res);
		printf("Status: %d\n", _status);
    }

    sqlite3_reset(res);
#endif

    int status = sqlite3_step(res);

    // We found nothing!
    if(status != SQLITE_ROW) {
    	printf("We found nothing!");
    	goto start;
    }
    else {
    	printf("Founded Results:");
	    do {
	        printf("\n\t%d|", sqlite3_column_int(res, 0));
	        printf("%s|", sqlite3_column_text(res, 1));
	        printf("%s|", sqlite3_column_text(res, 2));
	        printf("%s|", sqlite3_column_text(res, 3));
	        printf("%s|", sqlite3_column_text(res, 4));
	        printf("%s|", sqlite3_column_text(res, 5));
	        printf("%s|", sqlite3_column_text(res, 6));
	        printf("%s|", sqlite3_column_text(res, 7));
	        printf("%s\n", sqlite3_column_text(res, 8));
		} while (sqlite3_step(res) == SQLITE_ROW);

	    sqlite3_reset(res);

	    printf("Do you want to export the results as CSV?(y/n) ");
	    char yn;
	    scanf("%c", &yn);
	    while(getchar() != '\n');

	    // Create CSV file if user types y
	    if('y' == yn) {
	    	char file_name[255];
	    	// File name will be "search_by_(column_name_user_choosed)_(criteria_user_entered)"
	    	sprintf(file_name, "search_by_%s__%s.csv", column, criteria);
	    	FILE *csv_file = fopen(file_name, "w");
	    	if(NULL == csv_file) {
	    		fprintf(stderr, "Can't write results to CSV file!");
	    		// Skip the file writing because we failed to open it
	    		goto finish;
	    	}

	    	//First write the header
	    	fprintf(csv_file, "ID;Name;Surname;Phone;Mobilephone;Email;Address;City;Country\n");

	    	// Then write the results
	    	while (sqlite3_step(res) == SQLITE_ROW) {
	    		fprintf(csv_file, "%d;", sqlite3_column_int(res, 0));
		        fprintf(csv_file, "%s;", sqlite3_column_text(res, 1));
		        fprintf(csv_file, "%s;", sqlite3_column_text(res, 2));
		        fprintf(csv_file, "%s;", sqlite3_column_text(res, 3));
		        fprintf(csv_file, "%s;", sqlite3_column_text(res, 4));
		        fprintf(csv_file, "%s;", sqlite3_column_text(res, 5));
		        fprintf(csv_file, "%s;", sqlite3_column_text(res, 6));
		        fprintf(csv_file, "%s;", sqlite3_column_text(res, 7));
		        fprintf(csv_file, "%s\n", sqlite3_column_text(res, 8));
	    	}

	    	// Close the file
	    	fclose(csv_file);

			printf("Writed results to the CSV file \"%s\"", file_name);
	    }
	} // else
finish:
    sqlite3_finalize(res);
}

void ph_add(){
	char name[21],
		 surname[26],
		 phone[21],
		 mob_phone[26],
		 email[31],
		 address[126],
		 city[26],
		 country[26];

	// Get all the fields from user

	printf("Please enter the name: ");
	scanf("%20s", name);

	printf("Please enter the surname: ");
	scanf("%25s", surname);

	printf("Please enter the phone: ");
	scanf("%20s", phone);

	printf("Please enter the mobile phone: ");
	scanf("%25s", mob_phone);

	printf("Please enter the email: ");
	scanf("%30s", email);

	printf("Please enter the address: ");
	scanf("%125s", address);

	printf("Please enter the city: ");
	scanf("%25s", city);

	printf("Please enter the country: ");
	scanf("%25s", country);

#ifdef DEBUG
	printf("\nName: %s\nSurname: %s\nPhone: %s\nMobile Phone: %s\nEmail: %s\nAddress: %s\nCity: %s\nCountry: %s\n",
		name, surname, phone, mob_phone, email, address, city, country);
#endif

	char sql[255];

	// Prepare our insert statement
	snprintf(sql, 255, 
	"INSERT INTO phonebook"
		" (name, surname, phone, m_phone, email, address, city, country)"
		" VALUES ('%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
	name, surname, phone, mob_phone, email, address, city, country);

#ifdef DEBUG
	printf("SQL Statement: %s\n", sql);
#endif

	// Execute the statement, and give error, if it occured
	rc = sqlite3_exec(db, sql, NULL, NULL, NULL);
	if(SQLITE_OK != rc){
	 	fprintf(stderr, "SQL error: %s\n", sql_err);
	 	sqlite3_free(sql_err);
	 	exit(EXIT_FAILURE);
	}

	printf("Record added!");
}

void ph_update(){
	char sql[256];

	// Select all records from database to show user
	rc = sqlite3_prepare_v2(db, "SELECT * FROM phonebook", 255, &res, &tail);
	if(SQLITE_OK != rc){
	 	fprintf(stderr, "SQL error: %s\n", sql_err);
	 	sqlite3_free(sql_err);
	 	exit(EXIT_FAILURE);
	}

	while (sqlite3_step(res) == SQLITE_ROW) {
		printf("%d|", sqlite3_column_int(res, 0));
	    printf("%s|", sqlite3_column_text(res, 1));
	    printf("%s|", sqlite3_column_text(res, 2));
	    printf("%s|", sqlite3_column_text(res, 3));
	    printf("%s|", sqlite3_column_text(res, 4));
	    printf("%s|", sqlite3_column_text(res, 5));
	    printf("%s|", sqlite3_column_text(res, 6));
	    printf("%s|", sqlite3_column_text(res, 7));
	    printf("%s\n", sqlite3_column_text(res, 8));
	}

	sqlite3_finalize(res);

	printf("Please enter the id of the row which you want to edit: ");
	int id = 0;
	scanf("%d", &id);

	// Select the record from database, user selected
	// We will use this as default values.
	sprintf(sql, "SELECT * FROM phonebook WHERE id = %d", id);

	rc = sqlite3_prepare_v2(db, sql, 255, &res, &tail);
	if(SQLITE_OK != rc){
	 	fprintf(stderr, "SQL error: %s\n", sql_err);
	 	sqlite3_free(sql_err);
	 	exit(EXIT_FAILURE);
	}

	sqlite3_step(res);

	printf("Please enter the new details (leave blank if you do not want to change)\n\n");

	char name[21],
		 surname[26],
		 phone[21],
		 mob_phone[26],
		 email[31],
		 address[126],
		 city[26],
		 country[26];

	char *newline = "";

	fflush(stdin);
	while(getchar() != '\n');

	printf("Please enter the name: ");
	// More hack to allow user to enter empty charcter(newline)
	// scanf does not allow this so we are using fgets and doing parsing
	if (fgets(name, sizeof name, stdin) != NULL)
	{
		// Pointer to first occurence of newline character
		newline = strchr(name, '\n');
		if (newline)
			*newline = 0;
		// If the newline was at the beginnig of the string
		// now it will have 0 character count
		if (strlen(name) == 0)
		{
			// User does not want to change this
			// Leave it unchanged
			strcpy(name, sqlite3_column_text(res, 1));
		}
	}

	printf("Please enter the surname: ");
	if (fgets(surname, sizeof surname, stdin) != NULL)
	{
		newline = strchr(surname, '\n');
		if (newline)
			*newline = 0;
		if (strlen(surname) == 0) // input was empty
		{
			strcpy(surname, sqlite3_column_text(res, 2));
		}
	}

	printf("Please enter the phone: ");
	if (fgets(phone, sizeof phone, stdin) != NULL)
	{
	  newline = strchr(phone, '\n');
	  if (newline)
	    *newline = 0;

	  if (strlen(phone) == 0) // input was empty
	  {
	    strcpy(phone, sqlite3_column_text(res, 3));
	  }
	}

	printf("Please enter the mobile phone: ");
	if (fgets(mob_phone, sizeof mob_phone, stdin) != NULL)
	{
	  newline = strchr(mob_phone, '\n');
	  if (newline)
	    *newline = 0;

	  if (strlen(mob_phone) == 0) // input was empty
	  {
	    strcpy(mob_phone, sqlite3_column_text(res, 4));
	  }
	}

	printf("Please enter the email: ");
	if (fgets(email, sizeof email, stdin) != NULL)
	{
	  newline = strchr(email, '\n');
	  if (newline)
	    *newline = 0;

	  if (strlen(email) == 0) // input was empty
	  {
	    strcpy(email, sqlite3_column_text(res, 5));
	  }
	}

	printf("Please enter the address: ");
	if (fgets(address, sizeof address, stdin) != NULL)
	{
	  newline = strchr(address, '\n');
	  if (newline)
	    *newline = 0;

	  if (strlen(address) == 0) // input was empty
	  {
	    strcpy(address, sqlite3_column_text(res, 6));
	  }
	}

	printf("Please enter the city: ");
	if (fgets(city, sizeof city, stdin) != NULL)
	{
	  newline = strchr(city, '\n');
	  if (newline)
	    *newline = 0;

	  if (strlen(city) == 0) // input was empty
	  {
	    strcpy(city, sqlite3_column_text(res, 7));
	  }
	}

	printf("Please enter the country: ");
	if (fgets(country, sizeof country, stdin) != NULL)
	{
	  newline = strchr(country, '\n');
	  if (newline)
	    *newline = 0;

	  if (strlen(country) == 0) // input was empty
	  {
	    strcpy(country, sqlite3_column_text(res, 8));
	  }
	}

	sqlite3_finalize(res);

	// Prepare the SQL statement
	sprintf(sql, 
		"UPDATE phonebook"
		" SET name = '%s', surname = '%s', phone = '%s', m_phone = '%s',"
		" email = '%s', address = '%s', city = '%s', country = '%s'"
		" WHERE id = %d",
		name, surname, phone, mob_phone, email, address, city, country, id);
#ifdef DEBUG
	printf("SQL Statement: %s\n", sql);
#endif

	rc = sqlite3_exec(db, sql, NULL, NULL, &sql_err);
	if(SQLITE_OK != rc){
	 	fprintf(stderr, "SQL error: %s\n", sql_err);
	 	sqlite3_free(sql_err);
	}

	printf("Record #%d updated!", id);
}

void ph_delete(){
	// Show all records to user
	// Let them select an id
	// Delete that id :)

	rc = sqlite3_prepare_v2(db, "SELECT * FROM phonebook", 255, &res, &tail);
	if(SQLITE_OK != rc){
	 	fprintf(stderr, "SQLite error no: %d\n", rc);
	 	exit(EXIT_FAILURE);
	}

	while (sqlite3_step(res) == SQLITE_ROW) {
		printf("%d|", sqlite3_column_int(res, 0));
	    printf("%s|", sqlite3_column_text(res, 1));
	    printf("%s|", sqlite3_column_text(res, 2));
	    printf("%s|", sqlite3_column_text(res, 3));
	    printf("%s|", sqlite3_column_text(res, 4));
	    printf("%s|", sqlite3_column_text(res, 5));
	    printf("%s|", sqlite3_column_text(res, 6));
	    printf("%s|", sqlite3_column_text(res, 7));
	    printf("%s\n", sqlite3_column_text(res, 8));
	}

	sqlite3_finalize(res);

	int id;

	printf("Enter the id of the record which you want to delete: ");
	scanf("%d", &id);

	char sql[256];

	sprintf(sql, "DELETE FROM phonebook WHERE id = %d", id);

	rc = sqlite3_exec(db, sql, NULL, NULL, &sql_err);
	if(SQLITE_OK != rc){
	 	fprintf(stderr, "SQL error: %s\n", sql_err);
	 	sqlite3_free(sql_err);
	 	exit(EXIT_FAILURE);
	}

	printf("Record #%d is deleted!", id);
}