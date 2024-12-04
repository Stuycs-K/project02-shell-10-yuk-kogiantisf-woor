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

struct command_stack array_to_stack(struct command* cmds, int n) {
	struct command_stack out = init_stack(n*4);
	for (int i=0; i<n; i++) {
		push_command(&out, cmds[i]);
	}
	return out;
}

void print_command(struct command cmd) {
	printf("[%d]: %s\n", cmd.type, cmd.data);
}

void print_stack(struct command_stack stk) {
	printf("SP ->\t");
	print_command(stk.data[stk.sp]);
	for (int i=stk.sp-1; i>=0; i--) {
		printf("\t");
		print_command(stk.data[i]);
	}
}

int main(void) {
	struct command_stack stack = init_stack(10);
	print_stack(stack);
}

