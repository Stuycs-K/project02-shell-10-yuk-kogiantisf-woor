#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <unistd.h>
#include <sys/wait.h>
#include "processor.h"

#define PIPE_ACTIVE 0
#define ASYNC_ACTIVE 1
#define AND_ACTIVE 2
#define OR_ACTIVE 3

int execute_command(struct command cmd, struct command_stack* cmd_stack, int* status, int in, int out);
int execute_command_stack(struct command_stack*);

#endif
