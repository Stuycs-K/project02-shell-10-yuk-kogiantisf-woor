#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"

int process_commands_to_stack(struct command_stack* stack, struct command* cmds) {
	int n = 0;
	int status = 1;
	//Find out how big our array is
	for (; cmds[n].type != CMD_NULL; n++);
	//Now go backwards, until a pipe is found then go forwards
	for (int i=n-1; i>=0; i--) {
		if ((cmds[i].type == CMD_PIPE) || (i == 0)) {
			if (i == 0) status = push_command(stack, cmds[i]);
			int y = i+1;
			for (; y<n; y++)  {
				status = push_command(stack, cmds[y]);
				if (cmds[y].type == CMD_PIPE) break;
			}

		}
	}
	return status;
}

int push_command(struct command_stack* stack, struct command cmd) {
	//Check if stack is full
	if (stack->sp + 1 >= stack->stack_size) {
		return 0;
	}
	stack->sp++;
	int sp = stack->sp;
	stack->data[sp].type = cmd.type;
	for (int i=0; i<COMMAND_BUFF_SIZE; i++) {
		if (cmd.data[i] == NULL) {
			stack->data[sp].data[i] = NULL;
			break;
		}
		else {
			stack->data[sp].data[i] = (char*)malloc(sizeof(char)*strlen(cmd.data[i]));
			strcpy(stack->data[sp].data[i], cmd.data[i]);
		}
	}
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
	for (int i=0; i<COMMAND_BUFF_SIZE; i++) {
		if (stack->data[sp].data[i] == NULL) {
			out->data[i] = NULL;
			break;
		}
		else {
			out->data[i] = (char*)malloc(sizeof(char)*strlen(stack->data[sp].data[i]));
			strcpy(out->data[i], stack->data[sp].data[i]);
		}
	}
	stack->sp--;
	//Keep things memory safe
	for (int i=0; (stack->data[sp].data[i] != NULL) && (i<COMMAND_BUFF_SIZE); i++) {
		free(stack->data[sp].data[i]);
	}
	return out;
}

struct command create_command(int type, char** str) {
	struct command out;
	out.type = type;
	for (int i=0; i<COMMAND_BUFF_SIZE; i++) {
		if (str[i] == NULL) {
			out.data[i] = NULL;
		}
		else {
			out.data[i] = (char*)malloc(sizeof(char)*strlen(str[i]));
			strcpy(out.data[i], str[i]);
		}
	}
	return out;
}

struct command create_command_string(int type, char* str) {
	struct command out;
	char* str_m = (char*)malloc(sizeof(char)*strlen(str));
	strcpy(str_m, str);
	char** data = (char**)malloc(sizeof(char*)*COMMAND_BUFF_SIZE);
	//Trim off front whitespace
	for (; *(str_m) == ' '; str_m++);
	for (int i=0; i<COMMAND_BUFF_SIZE; i++) {
		char* buff = strsep(&str_m, " ");
		if (buff == NULL) {
			break;
		}
		if (strcmp(buff, "") == 0) {
			continue;
		}
		data[i] = buff;
	}
	out = create_command(type, data);
	free(str_m);
	return out;
}

struct command_stack init_stack(int size) {
	struct command_stack out;
	out.sp = 0;
	out.stack_size = size+1;
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
	printf("[%d]: ", cmd.type);
	for (int i=0; cmd.data[i] != NULL; i++) {
		printf("\"%s\" ", cmd.data[i]);
	}
	printf("\n");
}

void print_stack(struct command_stack stk) {
	printf("SP ->\t");
	print_command(stk.data[stk.sp]);
	for (int i=stk.sp-1; i>=0; i--) {
		printf("\t");
		print_command(stk.data[i]);
	}
}

void free_stack(struct command_stack* stack) {
	//Free other elements on stack
	while (pop_command(stack));
}

