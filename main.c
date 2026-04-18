#include <stdio.h>
#include <stdlib.h>
#include "string_parser.h"
#include "command.h"

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
			printf("%s, ", cmd.command_list[i]);
		}
		free_command_line(&cmd);
	}
	free(input_line);
	return 0;

}
