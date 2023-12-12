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
