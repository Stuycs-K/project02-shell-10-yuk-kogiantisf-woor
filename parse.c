#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

void parse_args( char * line, char ** arg_ary ){
    int i = 0;
    while (strchr(line, ' ') != NULL){
        arg_ary[i] = strsep(&line, " ");
        i++;
    }
    arg_ary[i] = line;
    arg_ary[i + 1] = NULL;
}