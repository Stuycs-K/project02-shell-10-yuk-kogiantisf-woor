#ifndef PARSE_H
#define PARSE_H

#include "processor.h"

#define MAX_DELIM_L 5

#define PARSE_ERR_ILLEGAL 2

int parse_input(struct command* out, char* line);
int count_str_instances(char* str, char* delim);
int str_in_arr(char* str, char** arr, int n);

#endif
