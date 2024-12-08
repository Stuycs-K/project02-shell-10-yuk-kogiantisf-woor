#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "parse.h"
#include "processor.h"
#include "executor.h"

#define INPUT_BUFFER_SIZE 1024 
#define PATH_BUFFER_SIZE 1024

#define STACK_SIZE 256

void print_prompt() {
	char path[PATH_BUFFER_SIZE];
	char* home = getenv("HOME");
	getcwd(path, PATH_BUFFER_SIZE);
	printf("\033[33m");
	if (strncmp(path, home, strlen(home)) == 0) {
		strcpy(path, path+strlen(home));
		printf("~");
	}
	printf("%s\033[1;0m> ", path);
	fflush(stdout);
}

int main() {
	int first_run = 1;
	struct command_stack stack = init_stack(STACK_SIZE);
	struct command parsed_commands[STACK_SIZE];
	while (1) {
		if (first_run) {
			printf("Welcome to \033[33mPEE\033[1;0m (Practical Execution Environment) Shell!\n");
			printf("Type \033[33mhelp\033[1;0m in the prompt if you need help!\n");
			first_run = 0;
		}

		char line[INPUT_BUFFER_SIZE];

		//Print the user prompt
		print_prompt();

		//read in user input
		if (fgets(line, INPUT_BUFFER_SIZE, stdin) == NULL) {
			return 0;
		}

		//remove newline at the end
		if (strchr(line, '\n') != NULL){
			*strchr(line, '\n') = '\0';
		}

		//parse user input
		parse_input(parsed_commands, line);

		//feed that user input onto the stack
		process_commands_to_stack(&stack, parsed_commands);

		//execute commands
		execute_command_stack(&stack);
	}

}
