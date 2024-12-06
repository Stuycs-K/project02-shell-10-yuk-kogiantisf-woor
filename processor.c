#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"

int in_list(char * s, char**ls){
  int i = 0;
  while (*(ls+i) != NULL){
    if (strcmp(s,*(ls+i)) == 0){
      return 0;
    }
    i += 1;
  }
  return 1;
}

// str is the first element of ary, which  is a list of strings in a command: ["ls",-a -l"]
// str should be null terminated
// 0 is regular commands
// 1 is redirects
// 2 is pipe
// 3 is colon
// 4 is special "cd" or "exit"
int assign_command(char * str){
  char* redirects[] = {">","<"};
  char* pipe[] = {"|"};
  char* colon[] = {";"};
  char* special[] = {"cd","exit"};
  int found = 0; //0 means not founds
  if (in_list(str,redirects) == 0){ //if str is in redirects, it returns 0
    return 1;
  }
  else if (in_list(str,pipe) == 0){ //if str is in redirects, it returns 0
    return 2;
  }
  else if (in_list(str,pipe) == 0){ //if str is in redirects, it returns 0
    return 3;
  }
  else if (in_list(str,special) == 0){ //if str is in redirects, it returns 0
    return 4;
  }
  else{
    return 0;
  }
  return -1;
}
/*
struct command* get_commands(char** str){
  int i;
  i = 0;
  int t;
  struct command* command_list = (struct command*) malloc(sizeof(struct command)*100);
  struct command temp;
  char * s = *(str);
  while (s != NULL){
    (command_list+i)->type = assign_command(s);
    strcpy((command_list+i)->data,s);
    i += 1;
    s = *(str+i);
  }
  return command_list;
}
*/

struct command* get_order(struct command* arr, int size){
  int i = 0;
  struct command temp;
  while (i < size){ // if "< b.txt"
    if (arr[i].type == 1){
      temp = arr[i];
      arr[i] = arr[i-1];
      arr[i-1] = temp;
    }
    printf("\n%s",arr[i].data[0]);
    i++;
  }
  return arr;
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
	for (int i=0; (i<COMMAND_BUFF_SIZE) && (data[i] = strsep(&str_m, " ")); i++);
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
		printf("%s ", cmd.data[i]);
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

