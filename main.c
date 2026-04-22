#include <stdio.h>
#include <stdlib.h>
#include "string_parser.h"
#include "command.h"
#include "string.h"
#include <unistd.h>

int running = 1;

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
	QUIT,
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
	if (strcmp(str, "quit") == 0) return QUIT;
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

int execute_command(command_line* args) {
	switch (get_command(args->command_list[0])) {
		case LS:
			if (args->num_token == 1) {
				listDir();
				return 0;
			}
			else {
				printf("Error! Unsupported parameters for command: ls\n");
				return 1;
			}
			break;
		case PWD:
			if (args->num_token == 1) {
				showCurrentDir();
				return 0;
			}
			else {
				printf("Error! Unsupported parameters for command: pwd\n");
				return 1;
			}
			break;
		case MKDIR:
			if (args->num_token == 2) {
				makeDir(args->command_list[1]);
				return 0;
			}
			else {
				printf("Error! Unsupported parameters for command: mkdir\n");
				return 1;
			}
			break;
		case CD:
			if (args->num_token == 2) {
				changeDir(args->command_list[1]);
				return 0;
			}
			else {
				printf("Error! Unsupported parameters for command: cd\n");
				return 1;
			}
			break;
		case CP:
			if (args->num_token == 3) {
				copyFile(args->command_list[1], args->command_list[2]);
				return 0;
			}
			else {
				printf("Error! Unsupported parameters for command: cp\n");
				return 1;
			}
			break;
		case MV:
			if (args->num_token == 3) {
				moveFile(args->command_list[1], args->command_list[2]);
				return 0;
			}
			else {
				printf("Error! Unsupported parameters for command: mv\n");
				return 1;
			}
			break;
		case RM:
			if (args->num_token == 2) {
				deleteFile(args->command_list[1]);
				return 0;
			}
			else {
				printf("Error! Unsupported parameters for command: rm\n");
				return 1;
			}
			break;
		case CAT:
			if (args->num_token == 2) {
				displayFile(args->command_list[1]);
				return 0;
			}
			else {
				printf("Error! Unsupported parameters for command: cat\n");
				return 1;
			}
			break;
		case QUIT:
			if (args->num_token == 1) {
				running = 0;
				return 0;
			}
			else {
				printf("Error! Unsupported parameters for command: quit\n");
				return 1;
			}
			break;
		case UNKNOWN:
			printf("Error! Unrecognized command: %s\n", args->command_list[0]);
			return 1;
			break;
	}
	return 1;
}	

int main(int argc, char* argv[]) {
	char *input_line = NULL;
	size_t len = 0;
	ssize_t read;
	FILE* input = stdin;

	if (argc == 3 && strcmp(argv[1], "-f") == 0) {
		input = fopen(argv[2], "r");
		if (input == NULL) {
			printf("Error: %s could not be opened\n", argv[2]);
			return 1;
		}
		freopen("output.txt", "w", stdout);
		setbuf(stdout, NULL);
		dup2(STDOUT_FILENO, STDERR_FILENO);
	}

	while (running) {
		if (input == stdin) {
			printf(">>> ");
		}
		read = getline(&input_line, &len, input);
		if (read != -1) {
			command_line cmd = str_tokenize(input_line);
			for (int i = 0; i < cmd.num_token; i++) {
				command_line args = space_split(trim(cmd.command_list[i]));
				if (args.num_token > 0) {
					if(execute_command(&args)) {
						free_command_line(&args);
						break;
					}
				}	
				free_command_line(&args);
			}		
			free_command_line(&cmd);	
		}
		else {
			break;
		}
		free(input_line);
		input_line = NULL;
		len = 0;
	}
	
	if (input != stdin) {
		fclose(input);
		printf("End of file\n");
		printf("Bye Bye!");
	}

	free(input_line);
	return 0;
}
