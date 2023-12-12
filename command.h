#ifndef COMMAND_H
#define COMMAND_H

#define MAX_ARGS 64

/**
 * struct command - Command structure
 * @name: Name of the command
 * @args: Arguments of the command
 */
struct command
{
	char *name;
	char *args[MAX_ARGS];
};

#endif /* COMMAND_H */
