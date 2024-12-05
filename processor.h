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
 * 4  - cd
 * 5  - exit
 * -1 - error (if not found)
 */

#define CMD_EXEC 0
#define CMD_REDIN 1
#define CMD_REDOUT 2
#define CMD_PIPE 3
#define CMD_CD 4
#define CMD_EXIT 5
#define CMD_ERR 6

#define COMMAND_BUFF_SIZE 64

struct command {
	int type;
	char* data[COMMAND_BUFF_SIZE];
};

struct command_stack {
	int sp;
	int stack_size;
	//This is an array
	struct command* data;
};

//Creates command struct
struct command create_command(int type, char** str);

//Create command by splitting by spaces
struct command create_command_string(int type, char* str);

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
void print_stack(struct command_stack stack);

//Free memory!
void free_stack(struct command_stack* stack);



#endif
