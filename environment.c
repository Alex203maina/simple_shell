#include "shell.h"

/**
 * display_environment - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int display_environment(info_t *info)
{
    print_list_str(info->environment);
    return (0);
}

/**
 * find_environment_variable - gets the value of an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: environment variable name
 *
 * Return: the value
 */
char *find_environment_variable(info_t *info, const char *name)
{
    list_t *node = info->environment;
    char *position;

    while (node)
    {
        position = starts_with(node->str, name);
        if (position && *position)
            return (position);
        node = node->next;
    }
    return (NULL);
}

/**
 * set_or_modify_environment - Initialize a new environment variable,
 *                             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int set_or_modify_environment(info_t *info)
{
    if (info->argc != 3)
    {
        _eputs("Incorrect number of arguments\n");
        return (1);
    }
    if (_set_environment_variable(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * remove_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int remove_environment_variable(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        _eputs("Too few arguments.\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        _remove_environment_variable(info, info->argv[i]);

    return (0);
}

/**
 * populate_environment_list - populates environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_environment_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->environment = node;
    return (0);
}


