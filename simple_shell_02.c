#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 64

struct command
{
	char *name;
	char *args[MAX_ARGS];
};

int main(void)
	char *cmd_name;
	char *cmd_args[MAX_ARGS];
	char cmd [MAX_CMD_LENGTH];
	int status;

	printf("$ ");

	fgets(cmd, MAX_CMD_LENGTH, stdin);
	cmd_name = cmd;

	char *token = strtok(cmd_name, " ");
	int i = 0;
	while (tiken != NULL && i < MAX_ARGS)
	{
		cmd_args[i++] = token;
		token = strtok(NULL, " ");
	}

	if (execvp(cmd_name, cmd_args) == -1)
	{
		perror("execvp");
		return (1);
	}

	wait(&status);

	return (0);
}
