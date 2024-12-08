#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"
#include "processor.h"
#include "executor.h"

#define INPUT_BUFFER_SIZE 200
#define PATH_BUFFER_SIZE 256

void print_prompt() {
	char path[PATH_BUFFER_SIZE];
	getcwd(path, PATH_BUFFER_SIZE);
	printf("\033[1;34m%s\033[1;0m$ ", path);
}

int main(){
    //main loop
    while (1){
        char line[INPUT_BUFFER_SIZE * 10];
        char** parsedcmd[INPUT_BUFFER_SIZE];

	//Allocate memory for the parsed commands
        for (int i=0; i < INPUT_BUFFER_SIZE; i++){
		parsedcmd[i] = malloc(INPUT_BUFFER_SIZE * sizeof(char *));
        }

	//Print the user prompt
	print_prompt();

        //read in user input
        fgets(line, INPUT_BUFFER_SIZE, stdin);
	int status = 0;
	struct command* out = parse_input(line, &status);
	for (int i=0; out[i].type != 0; i++) {
		print_command(out[i]);
	}
    }
	printf("\n");
}

