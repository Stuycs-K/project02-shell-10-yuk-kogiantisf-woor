#include <stdio.h>
#include "processor.h"
#include "executor.h"

int main(void) {
	struct command_stack stack = init_stack(12);
	push_command(&stack, create_command_string(CMD_EXEC, "cowsay"));
	push_command(&stack, create_command_string(CMD_REDIN, ".temp"));
	push_command(&stack, create_command_string(CMD_EXEC, "ls -l"));
	push_command(&stack, create_command_string(CMD_REDOUT, ".temp"));
	print_stack(stack);
	execute_command_stack(&stack);
}

