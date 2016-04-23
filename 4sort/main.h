#ifndef MAIN_H
#define MAIN_H

LARGE_INTEGER frequency;		// ticks per second
LARGE_INTEGER t1, t2;           // ticks

void start_timer();
double stop_timer();
void run_algorithm(int k, int *arr, int size);
int *read_from_file(char *file_name, int size);

#endif
