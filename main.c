#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"

int main(){
    //read in input
    printf("Enter a command:");
    int bufferSize = 200;
    char * args[bufferSize];
    char line[bufferSize * 10];
    char * lineptr = line;
    char * cmd;
    fgets(line, bufferSize, stdin);
    //get rid of newline character at end of line
    if (strchr(line, '\n') != NULL){
        *strchr(line, '\n') = '\0';
    }
    //split by semicolons if there multiple commands in a line
    while (strchr(lineptr, ';') != NULL){
        cmd = strsep(&lineptr, ";");
        parse_args(cmd,args);
        //test printing
        int i = 0;
        while (args[i] != NULL){
            printf("\"%s\"\n", args[i]);
            i++;
        }
    }
    cmd = strsep(&lineptr, ";");
    parse_args(cmd,args);
    //test printing
    int i = 0;
    while (args[i] != NULL){
        printf("\"%s\"\n", args[i]);
        i++;
    }
}