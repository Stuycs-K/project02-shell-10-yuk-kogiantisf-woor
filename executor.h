#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <unistd.h>
#include <sys/wait.h>
#include "processor.h"

#define PIPE_ACTIVE 0
#define ASYNC_ACTIVE 1
#define AND_ACTIVE 2
#define OR_ACTIVE 3

/* execute_command
 * 	executes a command
 *
 * ARGS
 * 	cmd - the command to execute
 * 	cmd_stack - if in the context of a command stack, the pointer to
 * 		    the command stack being used
 *	status - an array of integers denoting the status of certain intercommand conditions
 *	in - a file number of stdin (or whatever input you use)
 *	out - a file number of stdout (or whatever output you use)
 *
 * RETURN VALUE
 * 	1 (true) if command executed successfully
 * 	0 (false) if an error occured
 */	
int execute_command(struct command cmd, struct command_stack* cmd_stack, int* status, int in, int out);

/* execute_command_stack
 * 	executes commands from a command stack by popping
 * 	and running a command until the stack is empty
 *
 * ARGS
 * 	stack - a pointer to the command stack being used
 *
 * RETURN VALUE
 * 	1 (true) if the command stack was executed successfully
 * 	0 (false) if the command stack did not execute successfully
 */
int execute_command_stack(struct command_stack*);

#endif
