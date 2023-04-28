#include "shell.h"

/**
 * __get_file_history - gets the file's history
 * @info: params from the info struct
 * Return: string containg history file
 * allocated string
 */

char *__get_file_history(info_t *info)
{
    char *buf, *path_dir;

    path_dir = _getenv(info, "HOME=");
    if (!path_dir)
        return (NULL);
    buf = malloc(sizeof(char) * (_strlen(path_dir) + _strlen(HISTORY_FILE) + 2));
    if (!buf)
        return (NULL);
    buf[0] = 0;
    _strcpy(buf, path_dir);
    _strcat(buf, "/");
    _strcat(buf, HISTORY_FILE);
    return (buf);
}

/**
 * __write_history - writes to the file history
 * or creates a new file
 * or appends to an existing file
 * @info: params from the info struct
 * Return: 1 on success, else -1
 */
int __write_history(info_t *info)
{
    ssize_t file_dir;
    char *file_name = __get_file_history(info);
    list_t *node = NULL;

    if (!file_name)
        return (-1);

    file_dir = open(file_name, O_CREAT | O_TRUNC | O_RDWR, 0644);
    free(file_name);
    if (file_dir == -1)
        return (-1);
    for (node = info->history; node; node = node->next)
    {
        __puts_file_desc(node->str, file_dir);
        __put_file_desc('\n', file_dir);
    }
    __put_file_desc(BUFFER_FLUSH, file_dir);
    close(file_dir);
    return (1);
}

/**
 * __read_history - reads history
 * from a particular file
 * @info: params from the info struct
 * Return: history_count on success
 * 0 otherwise
 */
int __read_history(info_t *info)
{
    int i, last = 0, line_count = 0;
    ssize_t file_dir, read_length, file_size = 0;
    struct stat st;
    char *buf = NULL, *filename = __get_file_history(info);

    if (!filename)
        return (0);

    file_dir = open(filename, O_RDONLY);
    free(filename);
    if (file_dir == -1)
        return (0);
    if (!fstat(file_dir, &st))
        file_size = st.st_size;
    if (file_size < 2)
        return (0);
    buf = malloc(sizeof(char) * (file_size + 1));
    if (!buf)
        return (0);
    read_length = read(file_dir, buf, file_size);
    buf[file_size] = 0;
    if (read_length <= 0)
        return (free(buf), 0);
    close(file_dir);
    for (i = 0; i < file_size; i++)
        if (buf[i] == '\n')
        {
            buf[i] = 0;
            __build_history_list(info, buf + last, line_count++);
            last = i + 1;
        }
    if (last != i)
        __build_history_list(info, buf + last, line_count++);
    free(buf);
    info->history_count = line_count;
    while (info->history_count-- >= HISTORY_MAX)
        delete_node_at_index(&(info->history), 0);
    __re_number_history(info);
    return (info->history_count);
}

/**
 * __build_history_list - adds a new entry
 * to a history linked list
 * @info: params from the info struct
 * @buf: characters buffer
 * @line_count: the history linecount, history_count
 * Return: Always 0
 */
int __build_history_list(info_t *info, char *buf, int line_count)
{
    list_t *node = NULL;

    if (info->history)
        node = info->history;
    add_node_end(&node, buf, line_count);

    if (!info->history)
        info->history = node;
    return (0);
}

/**
 * __re_number_history - renumbers the history linked list
 * after any changes is encountered
 * @info: params from the info struct
 * Return: the new history_count
 */
int __re_number_history(info_t *info)
{
    list_t *node = info->history;
    int i = 0;

    while (node)
    {
        node->num = i++;
        node = node->next;
    }
    return (info->history_count = i);
}
