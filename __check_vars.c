#include "shell.h"

/**
 * __Is_chained - test if current char in buffer
 * is a chain delimeter i.e '||', '&&', ';'
 * @info: params from the info struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * Return: 1 if chain delimeter
 * 0 otherwise
 */
int __Is_chained(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->cmd_buffer_type = CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->cmd_buffer_type = CMD_AND;
    }
    else if (buf[j] == ';')
    {
        buf[j] = 0;
        info->cmd_buffer_type = CMD_CHAIN;
    }
    else
        return (0);
    *p = j;
    return (1);
}

/**
 * __chain_checks - checks for continuation
 * of chaining based on last status of the info struct
 * @info: the parameter struct
 * @info: params from the info struct
 * @p: address of current position in buffer
 * @i: starting position in buffer
 * @buff_length: length of buffer
 *
 * Return: Void
 */
void __chain_checks(info_t *info, char *buf, size_t *p, size_t i, size_t buff_length)
{
    size_t j = *p;

    if (info->cmd_buffer_type == CMD_AND)
    {
        if (info->status)
        {
            buf[i] = 0;
            j = buff_length;
        }
    }
    if (info->cmd_buffer_type == CMD_OR)
    {
        if (!info->status)
        {
            buf[i] = 0;
            j = buff_length;
        }
    }

    *p = j;
}

/**
 * replace_alias - replaces an aliases in a
 * found tokenized string
 * @info: params from the info struct
 * Return: 1 if found and replaced
 * 0 otherwise
 */
int replace_alias(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = node_starts_with(info->alias, info->argv[0], '=');
        if (!node)
            return (0);
        free(info->argv[0]);
        p = _strchr(node->str, '=');
        if (!p)
            return (0);
        p = _strdup(p + 1);
        if (!p)
            return (0);
        info->argv[0] = p;
    }
    return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: params from the info struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!_strcmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]),
                           _strdup(convert_number(info->status, 10, 0)));
            continue;
        }
        if (!_strcmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]),
                           _strdup(convert_number(getpid(), 10, 0)));
            continue;
        }
        node = node_starts_with(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replace_string(&(info->argv[i]),
                           _strdup(_strchr(node->str, '=') + 1));
            continue;
        }
        replace_string(&info->argv[i], _strdup(""));
    }
    return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return (1);
}
