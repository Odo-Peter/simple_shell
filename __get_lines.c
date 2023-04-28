#include "shell.h"
#include "main.h"

/**
 * input_buf - buffers chained commands
 * @info: info params from info struct
 * @buf: address of buffer
 * @var_length: address of var_length var
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *var_length)
{
    ssize_t r = 0;
    size_t length_p = 0;

    if (!*var_length)
    {
        free(*buf);
        *buf = NULL;
        signal(SIGINT, __handle_signals);
#if USE_SYSTEM_GETLINE
        r = getline(buf, &length_p, stdin);
#else
        r = _getline(info, buf, &length_p);
#endif
        if (r > 0)
        {
            if ((*buf)[r - 1] == '\n')
            {
                (*buf)[r - 1] = '\0';
                r--;
            }
            info->linecount_flag = 1;
            remove_comments(*buf);
            __build_history_list(info, *buf, info->history_count++);
            {
                *var_length = r;
                info->cmd_buffer = buf;
            }
        }
    }
    return (r);
}

/**
 * get_input - gets a line from stdin
 * minus the newline
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
    static char *buf;
    static size_t i, j, length_size;
    ssize_t r = 0;
    char **buf_p = &(info->arg), *p;

    _putchar(BUFFER_FLUSH);
    r = input_buf(info, &buf, &length_size);
    if (r == -1)
        return (-1);
    if (length_size)
    {
        j = i;
        p = buf + i;

        __chain_checks(info, buf, &j, i, length_size);
        while (j < length_size)
        {
            if (__Is_chained(info, buf, &j))
                break;
            j++;
        }

        i = j + 1;
        if (i >= length_size)
        {
            i = length_size = 0;
            info->cmd_buffer_type = CMD_DEFAULT;
        }

        *buf_p = p;
        return (_strlen(p));
    }

    *buf_p = buf;
    return (r);
}

/**
 * read_buffer - reads a buffer
 * @info: info params from info struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *i)
{
    ssize_t r = 0;

    if (*i)
        return (0);
    r = read(info->read_file_dir, buf, READ_BUFFER_SIZE);
    if (r >= 0)
        *i = r;
    return (r);
}

/**
 * _getline - gets the next line of input from the STDIN
 * @info: info params from info struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: if not NULL, size of
 * preallocated buffer
 * Return: the number of bytes read
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
    static char buf[READ_BUFFER_SIZE];
    static size_t i, len;
    size_t k;
    ssize_t r = 0, s = 0;
    char *p = NULL, *new_p = NULL, *c;

    p = *ptr;
    if (p && length)
        s = *length;
    if (i == len)
        i = len = 0;

    r = read_buffer(info, buf, &len);
    if (r == -1 || (r == 0 && len == 0))
        return (-1);

    c = _strchr(buf + i, '\n');
    k = c ? 1 + (unsigned int)(c - buf) : len;
    new_p = _realloc(p, s, s ? s + k : k + 1);
    if (!new_p)
        return (p ? free(p), -1 : -1);

    if (s)
        _strncat(new_p, buf + i, k - i);
    else
        _strncpy(new_p, buf + i, k - i + 1);

    s += k - i;
    i = k;
    p = new_p;

    if (length)
        *length = s;
    *ptr = p;
    return (s);
}

/**
 * __handle_signals - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void __handle_signals(__attribute__((unused)) int sig_num)
{
    _printf("\n");
    _prinf("Konichiwa :)$ ");
    _putchar(BUFFER_FLUSH);
}
