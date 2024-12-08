#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_TEMPFILE ".temp"

#define CMD_EXEC 1
#define CMD_REDIN 2
#define CMD_REDOUT 3
#define CMD_CD 4
#define CMD_REDOUTR 5
#define CMD_AND 6
#define CMD_OR 7
#define CMD_PIPE 8
#define CMD_ASYNC 9
#define CMD_EXIT 10
#define CMD_ERR 11
#define CMD_BREAK 12
#define CMD_HELP 13
#define CMD_NULL -1 

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

/* create_command
 *	creates a command struct from
 *	an array of strings
 *
 * ARGS:
 * 	type - the type of command
 * 	str - an array of strings representing the 
 * 		arguments of the command
 *
 * RETURN VALUE:
 * 	a command struct of type (type) and containing
 * 	the data inside of (str)
 */
struct command create_command(int type, char** str);

/* create_command_string
 * 	creates a command from a single string
 *
 * ARGS:
 * 	type - the type of command
 * 	str - a string representing the arguments
 * 		of the command
 *
 * RETURN VALUE:
 * 	a command struct of type (type) containing
 * 	the data inside of (str)
 */
struct command create_command_string(int type, char* str);

/* push_command
 * 	pushes a command to the command stack
 *
 * ARGS
 * 	stack - pointer to the command stack
 * 	cmd - command to push
 *
 * RETURN VALUE:
 * 	1 (true) on successful push
 * 	0 (false) if stack is full
 */
int push_command(struct command_stack* stack, struct command cmd);

/* process_commands_to_stack
 * 	takes an array of commands, which are
 * 	in the order of user input (this function is designed
 * 	to take the input from parse.c parse_input), and 
 * 	pushes them onto the command stack in the order in which
 * 	bash executes commands
 *
 * ARGS:
 * 	stack - the command stack to push to
 * 	cmds - an array of commands (most likely from parse.c parse_input)
 *
 * RETURN VALUE:
 * 	1 (true) on successful processing
 * 	0 (false) if an error occured
 */
int process_commands_to_stack(struct command_stack* stack, struct command* cmds);

/* pop_command
 * 	pops a command from the stack and returns it
 *
 * ARGS:
 * 	stack - a pointer to a command stack
 *
 * RETURN VALUE:
 * 	a pointer to a command popped from the stack
 * 	if the stack was empty, NULL is returned
 */
struct command* pop_command(struct command_stack* stack);

/* init_stack
 * 	initialized a stack of size (size)
 *
 * ARGS:
 * 	size - the size of the stack
 *
 * RETURN VALUE:
 * 	the stack that was initialized
 */
struct command_stack init_stack(int size);

/* print_command
 * 	prints a command
 *
 * ARGS:
 * 	cmd - the command to print
 *
 * RETURN VALUE:
 * 	none
 */
void print_command(struct command cmd);

/* print_stack
 * 	prints a stack, along with the stack pointer
 *
 * ARGS:
 * 	stack - the stack to print
 *
 * RETURN VALUE:
 * 	none
 */
void print_stack(struct command_stack stack);

/* free_stack
 * 	frees the memory on the command stack
 * 	it does this by calling pop_command() until the 
 * 	stack is empty. pop_command() frees the data
 * 	contained by a command.
 *
 * ARGS:
 * 	stack - the stack to free
 *
 * RETURN VALUE:
 * 	none
 */
void free_stack(struct command_stack* stack);

#endif
