#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parse.h"

int main(){
    //main loop
    while (1){
        int bufferSize = 200;
        char line[bufferSize * 10];
        char ** parsedcmd[bufferSize];
        for (int i = 0; i < bufferSize; i++){
            parsedcmd[i] = malloc(bufferSize * sizeof(char *));
        }
        //print current path prompt
        char path[bufferSize];
        getcwd(path, bufferSize);
        printf("\033[1;34m%s\033[1;0m$", path);
        //read in user input
        fgets(line, bufferSize, stdin);
        //get rid of newline character at end of line
        if (strchr(line, '\n') != NULL){
            *strchr(line, '\n') = '\0';
        }
        //split by semicolons if there multiple commands in a line
        char * lineptr = line;
        char * cmdptr;
        int semicolonsPresent = 1;
        while (semicolonsPresent == 1){
            if (strchr(lineptr, ';') == NULL){
                semicolonsPresent = 0;
            }
            cmdptr = strsep(&lineptr, ";");
            //split by redirects
            char * cmd = cmdptr;
            int redirectsPresent = 1;
            int pipe = 0;
            int i = 0;
            while (redirectsPresent == 1){
                if (strpbrk(cmdptr, "<>|") == NULL){
                    redirectsPresent = 0;
                }
                else{
                    cmdptr = strpbrk(cmdptr, "<>|");
                    *(cmdptr - 1) = '\0';
                    if (*cmdptr == '|'){
                        pipe = 1;
                        *(cmdptr + 1) = '\0';
                    }
                }
                parse_args(cmd,parsedcmd[i]);
                cmd = cmdptr;
                cmdptr++;
                if (pipe == 1){
                    pipe = 0;
                    cmdptr++;
                }
                i++;
            }
            //set final array to NULL
            parsedcmd[i] = NULL;
            //test printing
            i = 0;
            while (parsedcmd[i] != NULL){
                int j = 0;
                while (parsedcmd[i][j] != NULL){
                    printf("\"%s\"\n", parsedcmd[i][j]);
                    j++;
                }
                printf("\n");
                i++;
            }
            printf("new command\n\n");
        }
    }
    /*test commands
    echo 1;echo 2;echo 3;echo 4;echo 5;echo 6
    a < c.txt | b > d.txt;a < c.txt | b > d.txt;a < c.txt | b > d.txt
    a < c.txt | b > d.txt;echo 3
    a < c.txt | ls -l -a > d.txt;echo 1;a < c.txt | b > d.txt
    */
}