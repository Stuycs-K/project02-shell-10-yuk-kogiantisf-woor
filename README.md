[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Tfg6waJb)
# Systems Project2 - MyShell

## RFK's (Ronnie, Filippos, Kellen) Practical Execution Environment (PEE)
Group members: Ronnie Woo, Filippos Kogiantis, Kellen Yu

### Features
- General Functionality
	- Prompting user for input
	- Parsing the user input and separating commands by semicolons
	- Processing each command, forking, and then executing it
	- Printing user prompt with the ```cwd``` path
	- Implementing the ```cd``` and ```exit``` commands
	- Implementing redirection and piping
- Infinite piping
	- Piping does use a tempfile, but you can chain together infinitely many (as much as the buffer can hold) commands with pipes. i.e: ```a | b | c | d```
- Whitespaces not needed between special characters
	- ```a|b, a>b, a<b``` are valid
- Quotations (sometimes)
	- ```a > "b amongus.txt", etc``` works

### Unimplemented but attemped
- ```&&, ||, and &``` commands

### Bugs

### Function Reference
`processor.h`
```c
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
```
`executor.h`
```c
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
```
`parse.h`
```c
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
 * 	the amount of occurrences of (delim) in (str)
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
```




