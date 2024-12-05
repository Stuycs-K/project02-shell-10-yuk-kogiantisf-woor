#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "processor.h"

int execute_command(struct command cmd) {
	switch(cmd.type) {
		case CMD_EXEC:
			pid_t p = fork();
			if (p == 0) {
				execvp(cmd.data[0], cmd.data);
				exit(0);
			}
			int status;
			waitpid(p, &status, 0);
			break;
		case CMD_REDIN:
			break;
		case CMD_PIPE:
			break;
		case CMD_CD:
			break;
		case CMD_EXIT:
			break;
		case CMD_ERR:
			return 0;
			break;
		default:
			return 0;
			break;
	}
	return 1;
}

int execute_command_stack(struct command_stack* cmd_stack) {
	struct command* cmd;
	while (cmd = pop_command(cmd_stack)) {
		execute_command(*cmd);
	}
	return 1;
}

int main(void) {
	struct command_stack stack = init_stack(12);
	push_command(&stack, create_command_string(CMD_EXEC, "ls -l"));
	execute_command_stack(&stack);

}

