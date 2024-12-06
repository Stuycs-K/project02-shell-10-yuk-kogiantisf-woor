#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "processor.h"

int execute_command(struct command cmd, int in, int out) {
	switch(cmd.type) {
		case CMD_EXEC:
			pid_t p = fork();
			if (p == 0) {
				execvp(cmd.data[0], cmd.data);
				exit(0);
			}
			int status;
			waitpid(p, &status, 0);
			dup2(out, STDOUT_FILENO);
			dup2(in, STDIN_FILENO);
			break;
		case CMD_REDIN:
			int new_in = open(cmd.data[0], O_RDONLY);
			dup2(new_in, STDIN_FILENO);
			break;
		case CMD_REDOUT:
			printf("REDIRECTING\n");
			int new_out = open(cmd.data[0], O_WRONLY | O_CREAT, 0644);
			dup2(new_out, STDOUT_FILENO);
			break;
		case CMD_PIPE:
			dup2(out, STDIN_FILENO);
			dup2(in, STDOUT_FILENO);
			break;
		case CMD_CD:
			chdir(cmd.data[0]);
			break;
		case CMD_EXIT:
			exit(0);
			break;
		case CMD_ERR:
			return 0;
			break;
		default:
			fprintf(stderr, "Undefined command!\n");
			return 0;
			break;
	}
	return 1;
}

int execute_command_stack(struct command_stack* cmd_stack) {
	struct command* cmd;
	int in = dup(STDIN_FILENO);
	int out = dup(STDOUT_FILENO);
	while (cmd = pop_command(cmd_stack)) {
		execute_command(*cmd, in, out);
	}
	return 1;
}
