#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include "processor.h"
#include "executor.h"

int execute_command(struct command cmd, struct command_stack* cmd_stack, int* status, int in, int out) {
	int new_out;
	int new_in;
	switch(cmd.type) {
		case CMD_EXEC:
			pid_t p = fork();
			if (p == 0) {
				execvp(cmd.data[0], cmd.data);
				exit(0);
			}
			int pid_status;
			waitpid(p, &pid_status, 0);
			dup2(out, STDOUT_FILENO);
			dup2(in, STDIN_FILENO);
			if (status[PIPE_ACTIVE]) {
				new_in = open(CMD_TEMPFILE, O_RDONLY);
				dup2(new_in, STDIN_FILENO);
				status[PIPE_ACTIVE] = 0;
			}
			break;
		case CMD_REDIN:
			new_in = open(cmd.data[0], O_RDONLY);
			dup2(new_in, STDIN_FILENO);
			break;
		case CMD_REDOUT:
			new_out = open(cmd.data[0], O_WRONLY | O_CREAT, 0644);
			dup2(new_out, STDOUT_FILENO);
			break;
		case CMD_CD:
			chdir(cmd.data[0]);
			break;
		case CMD_REDOUTR:
			new_out = open(cmd.data[0], O_APPEND | O_CREAT | O_WRONLY, 0644);
			dup2(new_out, STDOUT_FILENO);
			break;
		case CMD_AND:
			status[OR_ACTIVE] = 1;
			break;
		case CMD_OR:
			status[AND_ACTIVE] = 1;
			break;
		case CMD_PIPE:
			new_out = open(CMD_TEMPFILE, O_WRONLY | O_CREAT, 0644);
			dup2(new_out, STDOUT_FILENO);
			status[PIPE_ACTIVE] = 1;
			break;
		case CMD_ASYNC:
			status[ASYNC_ACTIVE] = 1;
			break;
		case CMD_EXIT:
			free_stack(cmd_stack);
			dup2(out, STDOUT_FILENO);
			dup2(in, STDIN_FILENO);
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
	int status[4] = {0};
	while (cmd = pop_command(cmd_stack)) {
		execute_command(*cmd, cmd_stack, status, in, out);
	}
	return 1;
}
