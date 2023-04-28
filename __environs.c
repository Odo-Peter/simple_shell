#include "shell.h"

/**
 * __env - prints the current environment
 * @info: params from the info struct
 * Return: 0 in success
 */
int __env(info_t *info)
{
    print_list_str(info->env);
    return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: params from the info struct
 * @env_name: environment variable
 * Return: the of the env
 */
char *_getenv(info_t *info, const char *env_name)
{
    list_t *node = info->env;
    char *p;

    while (node)
    {
        p = starts_with(node->str, env_name);
        if (p && *p)
            return (p);
        node = node->next;
    }
    return (NULL);
}

/**
 * __setenv - Initialize a new env variable
 * or modify an existing one
 * @info: params from the info struct
 *  Return: Always 0
 */
int __setenv(info_t *info)
{
    if (info->argc != 3)
    {
        __error_puts("Incorrect number of arguments\n");
        return (1);
    }
    if (_setenv(info, info->argv[1], info->argv[2]))
        return (0);
    return (1);
}

/**
 * __unsetenv - Remove an env variable
 * @info: params from the info struct
 * Return: 0 on success
 */
int __unsetenv(info_t *info)
{
    int i;

    if (info->argc == 1)
    {
        __error_puts("Too few arguments, check please\n");
        return (1);
    }
    for (i = 1; i <= info->argc; i++)
        _unsetenv(info, info->argv[i]);

    return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: params from the info struct
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
    list_t *node = NULL;
    size_t i;

    for (i = 0; environ[i]; i++)
        add_node_end(&node, environ[i], 0);
    info->env = node;
    return (0);
}
