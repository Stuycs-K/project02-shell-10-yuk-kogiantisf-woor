#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"

int push_command(struct command_stack* stack, struct command cmd) {
	//Check if stack is full
	if (stack->sp + 1 >= stack->stack_size) {
		return 0;
	}
	stack->sp++;
	int sp = stack->sp;
	stack->data[sp].type = cmd.type;
	strcpy(stack->data[sp].data, cmd.data);
	return 1;
}

struct command* pop_command(struct command_stack* stack) {
	//Check if stack is empty
	if (stack->sp - 1 < 0) {
		return NULL;
	}
	int sp = stack->sp;
	struct command* out = (struct command*)malloc(sizeof(struct command));
	out->type = stack->data[sp].type;
	strcpy(out->data, stack->data[sp].data);
	stack->sp--;
	return out;
}

void print_command(struct command* command) {
	printf("Type: %d | Data: %s\n", command->type, command->data);
}

struct command create_command(int type, char* str) {
	struct command out;
	out.type = type;
	strcpy(out.data, str);
	return out;
}

struct command_stack init_stack(int size) {
	struct command_stack out;
	out.sp = 0;
	out.stack_size = size;
	out.data = (struct command*)malloc(sizeof(struct command)*size);
	return out;
}

int main(void) {
	struct command_stack stack = init_stack(10);
	push_command(&stack, create_command(1, "abc"));
	push_command(&stack, create_command(2, "a,monmgus"));
	push_command(&stack, create_command(3, "addbc"));
	push_command(&stack, create_command(1, "fffabc"));


	print_command(pop_command(&stack));
	print_command(pop_command(&stack));

	push_command(&stack, create_command(1, "AAA"));
	print_command(pop_command(&stack));
	print_command(pop_command(&stack));
	print_command(pop_command(&stack));

}
