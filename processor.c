#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "processor.h"



int in_list(char * s, char**ls){
  int i = 0;
  while (*(ls+i) != NULL){
    if (strcmp(s,*(ls+i)) == 0){
      return 0;
    }
    i += 1;
  }
  return 1;
}

// str is the first element of ary, which  is a list of strings in a command: ["ls",-a -l"]
// str should be null terminated
// 0 is regular commands
// 1 is redirects
// 2 is pipe
// 3 is colon
// 4 is special "cd" or "exit"
int assign_command(char * str){
  char* redirects[] = {">","<"};
  char* pipe[] = {"|"};
  char* colon[] = {";"};
  char* special[] = {"cd","exit"};
  int found = 0; //0 means not founds
  if (in_list(str,redirects) == 0){ //if str is in redirects, it returns 0
    return 1;
  }
  else if (in_list(str,pipe) == 0){ //if str is in redirects, it returns 0
    return 2;
  }
  else if (in_list(str,colon) == 0){ //if str is in redirects, it returns 0
    return 3;
  }
  else if (in_list(str,special) == 0){ //if str is in redirects, it returns 0
    return 4;
  }
  else{
    return 0;
  }
  return -1;
}

struct command* get_commands(char** str){
  int i;
  i = 0;
  int t;
  struct command* command_list = (struct command*) malloc(sizeof(struct command)*100);
  struct command temp;
  char * s = *(str);
  while (s != NULL){
    (command_list+i)->type = assign_command(s);
    strcpy((command_list+i)->data,s);
    i += 1;
    s = *(str+i);
  }
  return command_list;
}
