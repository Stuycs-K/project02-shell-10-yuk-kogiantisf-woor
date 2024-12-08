#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "processor.h"

int count_str_instances(char* str, char* delim) {
	if (strlen(str) < strlen(delim)) {
		return 0;
	}
	int count = 0;
	int delim_l = strlen(delim);
	char* str_p = str;
	char* buff = (char*)malloc(sizeof(char)*delim_l+1);
	//Make sure to null terminate
	buff[delim_l] = '\0';
	for (int i=0; i<strlen(str)-delim_l; i++) {
		strncpy(buff, str_p, delim_l);
		if (strcmp(buff, delim) == 0) {
			count++;
		}
		str_p++;
	}
	free(buff);
	return count;
}

int str_in_arr(char* str, char** arr, int n) {
	for (int i=0; i<n; i++) {
		if (strcmp(str, arr[i])==0) {
			return 1;
		}
	}
	return 0;
}

int parse_input(struct command* out, char* line) {
	char* s_token;
	//char* delims[] = {">", "<", "|", "&", ">>", "&&", "||", "cd", "exit", ";"};
	char delimc[] = "><|&;";
	int n = 0;
	char* buff = (char*)malloc(sizeof(char)*MAX_DELIM_L);
	int len = strlen(line);
	for (int i=0; i < len; ) {
		if (line[i] == '\0') {
			break;
		}
		int type = CMD_EXEC;
		strncpy(buff, line+i, MAX_DELIM_L);
		if ((buff[0] == '>') && (buff[1] != '>')) {
			i++;
			type = CMD_REDOUT;
		}
		else if ((buff[0] == '>') && (buff[1] == '>')) {
			i+=2;
			type = CMD_REDOUTR;
		}
		else if (buff[0] == '<') {
			i++;
			type = CMD_REDIN;
		}
		else if ((buff[0] == '|') && (buff[1] != '|')) {
			i++;
			type = CMD_PIPE;
			out[n] = create_command_string(type, "PIPE");
			n++;
			continue;
		}
		else if ((buff[0] == '|') && (buff[1] == '|')) {
			i+=2;
			type = CMD_OR;
			out[n] = create_command_string(type, "OR");
			n++;
			continue;
		}
		else if ((buff[0] == '&') && (buff[1] != '&')) {
			i++;
			type = CMD_ASYNC;
			out[n] = create_command_string(type, "ASYNC");
			n++;
			continue;
		}
		else if ((buff[0] == '&') && (buff[1] == '&')) {
			i+=2;
			type = CMD_AND;
			out[n] = create_command_string(type, "AND");
			n++;
			continue;
		}
		else if ((buff[0] == 'c') && (buff[1] == 'd') && ((buff[2] == '\0') || (buff[2] == ' '))) {
			i+=3;
			type = CMD_CD;
		}
		else if (buff[0] == ';') {
			i++;
			continue;
		}
		else if (
				(buff[0] == 'e') && 
				(buff[1] == 'x') && 
				(buff[2] == 'i') &&
				(buff[3] == 't') &&
				((buff[4] == '\0') || (buff[4] == ' '))
			) {
			i+=5;
			type = CMD_EXIT;
			out[n] = create_command_string(type, "EXIT");
			n++;
			continue;


		}
		free(buff);

		int r=i;
		while (strchr(delimc, line[r]) == NULL) {
			r++;
		}
		char* dbuff = (char*)calloc(r-i+1, sizeof(char));
		strncpy(dbuff, line+i, r-i);
		printf("dbuff: \"%s\"\n", dbuff);
		out[n] = create_command_string(type, dbuff);
		n++;
		i=r;
	}
	out[n].type = CMD_NULL;
	return 1;
}
