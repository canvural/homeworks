// Some helper functions and variables

static const char filename[] = "commands.txt";
char lineG [255];

// Variables for using while parsing a line
char command,
	 soldier_info[255];

int army,
	health,
	strength,
	health_,
	strength_;

int dead_count,
	dead_count_;
float damage_count,
	  damage_count_;

// Flag for turn
// 1 for first army, 0 for second
int turn;

char *read_line();

// A little math trick to concat two integers
int concatenate(int x, int y);