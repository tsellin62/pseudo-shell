#include <stdio.h>
#include <stdlib.h>
#include "string_parser.h"
#include "command.h"
#include "string.h"

//enum to help choose command
typedef enum {
	LS,
	PWD,
	MKDIR,
	CD,
	CP,
	MV,
	RM,
	CAT,
	UNKNOWN
} command_type;

//get command
command_type get_command(char* str) {
	if (strcmp(str, "ls") == 0) return LS;
	if (strcmp(str, "pwd") == 0) return PWD;
	if (strcmp(str, "mkdir") == 0) return MKDIR;
	if (strcmp(str, "cd") == 0) return CD;
	if (strcmp(str, "cp") == 0) return CP;
	if (strcmp(str, "mv") == 0) return MV;
	if (strcmp(str, "rm") == 0) return RM;
	if (strcmp(str, "cat") == 0) return CAT;
	return UNKNOWN;
}

//trim leading and trailing whitespace
char* trim(char* str) {
	while (*str == ' ' || *str == '\n' || *str == '\r') {
		str++;
	}
	char* end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\n' || *end == '\r')) {
		*end = '\0';
		end--;
	}
	return str;
}

//same as str_tokenize but for splitting with a space
command_line space_split(char* str) {
	command_line cmd;
	int count = 0;
	char** lst = (char**)malloc(sizeof(char*));
	char* token = strtok(str, " ");
	while (token != NULL) {
		lst = realloc(lst, (count + 1) * sizeof(char*));
		lst[count] = strdup(token);
		count++;
		token = strtok(NULL, " ");
	}
	cmd.num_token = count;
	cmd.command_list = lst;
	return cmd;
}

void execute_command(command_line* args) {
	switch (get_command(args->command_list[0])) {
		case LS:
			if (args->num_token == 1) {
				listDir();
			}
			else {
				printf("Error! Unsupported parameters for command: ls\n");
			}
			break;
		case PWD:
			if (args->num_token == 1) {
				showCurrentDir();
			}
			else {
				printf("Error! Unsupported parameters for command: pwd\n");
			}
			break;
		case MKDIR:
			if (args->num_token == 2) {
				makeDir(args->command_list[1]);
			}
			else {
				printf("Error! Unsupported parameters for command: mkdir\n");
			}
			break;
		case CD:
			if (args->num_token == 2) {
				changeDir(args->command_list[1]);
			}
			else {
				printf("Error! Unsupported parameters for command: cd\n");
			}
			break;
		case CP:
			if (args->num_token == 3) {
				copyFile(args->command_list[1], args->command_list[2]);
			}
			else {
				printf("Error! Unsupported parameters for command: cp\n");
			}
			break;
		case MV:
			if (args->num_token == 3) {
				moveFile(args->command_list[1], args->command_list[2]);
			}
			else {
				printf("Error! Unsupported parameters for command: mv\n");
			}
			break;
		case RM:
			if (args->num_token == 2) {
				deleteFile(args->command_list[1]);
			}
			else {
				printf("Error! Unsupported parameters for command: rm\n");
			}
			break;
		case CAT:
			if (args->num_token == 2) {
				displayFile(args->command_list[1]);
			}
			else {
				printf("Error! Unsupported parameters for command: cat\n");
			}
			break;
		case UNKNOWN:
			printf("Error! Unrecognized command: %s\n", args->command_list[0]);
			break;
	}
}	

int main(int argc, char* argv[]) {
	char *input_line = NULL;
	size_t len = 0;
	ssize_t read;
	printf(">>> ");
	read = getline(&input_line, &len, stdin);
	if (read != -1) {
		command_line cmd = str_tokenize(input_line);
		printf("%d\n", cmd.num_token);
		for (int i = 0; i < cmd.num_token; i++) {
			command_line args = space_split(cmd.command_list[i]);
			execute_command(&args);
			free_command_line(&args);
		}		
		free_command_line(&cmd);	
	}
	free(input_line);
	return 0;

}
