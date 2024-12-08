#ifndef PARSE_H
#define PARSE_H

#include "processor.h"

#define MAX_DELIM_L 5

/* parse_input
 * 	Parses a line of user input into an array of commands
 *
 * ARGS:
 * 	out - an array of commands 
 * 	line - the raw input from a user
 *
 * RETURN VALUE:
 * 	returns a 1 if successfully parsed, a 0 if failed
 */
int parse_input(struct command* out, char* line);

/* count_str_instances
 * 	counts the amount of times a string (delim) 
 * 	occurs in another string (str)
 *
 * ARGS:
 * 	str - the string to search in
 * 	delim - the string to look for
 *
 * RETURN VALUE:
 * 	the amount of occurances of (delim) in (str)
 */
int count_str_instances(char* str, char* delim);

/* str_in_arr
 * 	returns 1 (true) if a string (str) is contained
 * 	in an array of strings (arr).
 *
 * ARGS:
 * 	str - the string you want to check
 * 	arr - the array of strings
 *
 * RETURN VALUE:
 * 	1 (true) if (str) does appear in (arr)
 * 	0 (false) if (str) does not appear in (arr)
 */
int str_in_arr(char* str, char** arr, int n);

#endif
