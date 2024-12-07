#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

//takes a command line and an array of char *, and assigns each pointer in the char * array to each argument in the command, and sets the final pointer to point to NULL
void parse_args( char * line, char ** arg_ary ){
    int i = 0;
    int spacesPresent = 1;
    while (strchr(line, ' ') != NULL){
        // if (strchr(line, ' ') == NULL){
        //     spacesPresent = 0;
        // }
        // printf("%d\n", *arg_ary[i]);
        arg_ary[i] = strsep(&line, " ");
        i++;
    }
    arg_ary[i] = line;
    arg_ary[i+1] = NULL;
}