#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <unistd.h>
#include <sys/wait.h>
#include "processor.h"

int execute_command(struct command cmd, struct command_stack cmd_stack, int in, int out);
int execute_command_stack(struct command_stack*);

#endif
