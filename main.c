#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"

int main(){
    printf("Enter a command:");
    int bufferSize = 200;
    char * args[bufferSize];
    char line[bufferSize * 10];
    char * lineptr = line;
    char * cmd;
    fgets(line, bufferSize, stdin);
    // while (strchr(line, ';') != NULL){
    //     cmd = strsep(&line, ';');
    //     parse_args(line,args);
    //     execvp(args[0], args);
    // }
    cmd = strsep(&lineptr, ";");
    parse_args(cmd,args);
    printf("%s\n", args[0]);
    printf("%s\n", args[1]);
    execvp(args[0], args);
}