#ifndef PROCESSOR_H
#define PROCESSOR_H

/* types of commands
 * 0 - executable
 * 1 - redirect to stdin
 * 2 - redirect to stdout
 * 3 - pipe
 * 4 - cd
 */

struct command {
	int type;
	char data[128];
};

struct command_stack {
	int sp;
	struct command* stack;
};

void push_command(struct command);
void pop_command(struct command);

struct command* get_commands(char** str);


#endif 
