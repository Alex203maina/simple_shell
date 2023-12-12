#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 64

/**
 * get_command - Reads a command from the user
 * @cmd: A pointer to a buffer where the command will be stored
 *
 * Return: Nothing
 */
void get_command(char *cmd)
	{
		printf("$ ");
		fgets(cmd, MAX_CMD_LENGTH, stdin);
	}

/**
 * tokenize_command - Splits a command into tokens
 * @cmd: The command to be tokenized
 * @cmd_args: An array of pointers where the tokens will be stored
 *
 * Return: Nothing
 */
void tokenize_command(char *cmd, char **cmd_args)
	{
		char *token = strtok(cmd, " ");
		int i = 0;

		while (token != NULL && i < MAX_ARGS)
		{
			cmd_args[i++] = token;
			token = strtok(NULL, " ");
		}
	}

/**
 * execute_command - Executes a command using execvp
 * @cmd_name: The name of the command
 * @cmd_args: The arguments of the command
 *
 * Return: Nothing
 */
int execute_command(char *cmd_name, char **cmd_args)
	{
		if (execvp(cmd_name, cmd_args) == -1)
		{
			perror("execvp");
			return (1);
		}
		return (0);
	}

/**
 * main - Start Point
 *
 * Return: Always 0 (Success)
 */
int main(void)
{
	struct command cmd_struct;
	char cmd[MAX_CMD_LENGTH];
	int status;

	get_command(cmd);
	cmd_struct.name = cmd;
	tokenize_command(cmd, cmd_struct.args);
	execute_command(cmd_struct.name, cmd_struct.args);

	/* Wait for the completion of command */
	wait(&status);

	return (0);
}
