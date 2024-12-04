#ifndef PROCESSOR_H
#define PROCESSOR_H

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

struct command create_command(int type, char* str);

int push_command(struct command_stack* stack, struct command cmd);

struct command* pop_command(struct command_stack* stack);

struct command* get_commands(char** str);

struct command_stack init_stack(size);


#endif
