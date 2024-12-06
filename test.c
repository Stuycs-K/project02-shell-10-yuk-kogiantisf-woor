#include <stdio.h>
#include "processor.h"
#include "executor.h"

int main(void) {
	struct command_stack stack = init_stack(12);
	push_command(&stack, create_command_string(CMD_EXEC));
	print_stack(stack);
	execute_command_stack(&stack);
}

