#include "shell.h"

/**
 * display_history - displays the history list, one command by line, preceded
 *                   with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int display_history(info_t *info)
{
    print_list(info->history);
    return (0);
}

/**
 * remove_alias - removes alias by string
 * @info: parameter struct
 * @alias_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(info_t *info, char *alias_str)
{
    char *equal_sign, temp_char;
    int result;

    equal_sign = _strchr(alias_str, '=');
    if (!equal_sign)
        return (1);

    temp_char = *equal_sign;
    *equal_sign = 0;

    result = delete_node_at_index(&(info->alias),
                                  get_node_index(info->alias, node_starts_with(info->alias, alias_str, -1)));

    *equal_sign = temp_char;
    return result;
}

/**
 * set_new_alias - sets alias to string
 * @info: parameter struct
 * @alias_str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_new_alias(info_t *info, char *alias_str)
{
    char *equal_sign_position;

    equal_sign_position = _strchr(alias_str, '=');
    if (!equal_sign_position)
        return (1);

    if (!*++equal_sign_position)
        return remove_alias(info, alias_str);

    remove_alias(info, alias_str);
    return (add_node_end(&(info->alias), alias_str, 0) == NULL);
}

/**
 * print_single_alias - prints an alias string
 * @alias_node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_single_alias(list_t *alias_node)
{
    char *equal_sign_position = NULL, *current_char = NULL;

    if (alias_node)
    {
        equal_sign_position = _strchr(alias_node->str, '=');
        for (current_char = alias_node->str; current_char <= equal_sign_position; current_char++)
            _putchar(*current_char);

        _putchar('\'');
        _puts(equal_sign_position + 1);
        _puts("'\n");
        return (0);
    }
    return (1);
}

/**
 * handle_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int handle_alias(info_t *info)
{
    int index = 0;
    char *equal_sign_position = NULL;
    list_t *current_alias_node = NULL;

    if (info->argc == 1)
    {
        current_alias_node = info->alias;
        while (current_alias_node)
        {
            print_single_alias(current_alias_node);
            current_alias_node = current_alias_node->next;
        }
        return (0);
    }

    for (index = 1; info->argv[index]; index++)
    {
        equal_sign_position = _strchr(info->argv[index], '=');
        if (equal_sign_position)
            set_new_alias(info, info->argv[index]);
        else
            print_single_alias(node_starts_with(info->alias, info->argv[index], '='));
    }

    return (0);
}

