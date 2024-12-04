#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* types of commands
 * 0  - executable
 * 1  - redirect to stdin
 * 2  - redirect to stdout
 * 3  - pipe
 * 4  - cd or exit
 * -1 - if not found
 */

struct command {
	int type;
	char data[128];
};

struct command_stack {
	int sp;
	int stack_size;
	struct command* data;
};

//Creates command struct
struct command create_command(int type, char* str);

//Pushes a command struct to a command stack, 1 for success, 0 for stack full
int push_command(struct command_stack* stack, struct command cmd);

//Pops command from the command stack, returns NULL ptr if stack is empty
struct command* pop_command(struct command_stack* stack);

//Turns the output of the parser into a stack of commands
struct command* get_commands(char** str);

//Create an empty stack
struct command_stack init_stack(int size);

//Turn an array
struct command_stack array_to_stack(struct command* cmds, int n);

void print_command(struct command cmd);



#endif
