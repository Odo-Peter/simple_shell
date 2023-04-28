#include "shell.h"

/**
 * __error_puts - prints an input string to stderr
 * @str: the string to be printed
 * Return: void function
 */
void __error_puts(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        __error_putchar(str[i]);
        i++;
    }
}

/**
 * __error_putchar - writes a character c to stderr
 * @c: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int __error_putchar(char c)
{
    static int i;
    static char buf[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUFFER_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * __put_file_desc - writes the character c
 * to a given file descriptor
 * @c: The character to print
 * @file_desc: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int __put_file_desc(char c, int file_desc)
{
    static int i;
    static char buf[WRITE_BUFFER_SIZE];

    if (c == BUFFER_FLUSH || i >= WRITE_BUFFER_SIZE)
    {
        write(file_desc, buf, i);
        i = 0;
    }
    if (c != BUFFER_FLUSH)
        buf[i++] = c;
    return (1);
}

/**
 * __puts_file_desc - prints an input string
 * @str: the string to be printed
 * @file_desc: the file descriptor to write to
 *
 * Return: the number of chars put
 */
int __puts_file_desc(char *str, int file_desc)
{
    int i = 0;

    if (!str)
        return (0);
    while (*str)
    {
        i += __put_file_desc(*str++, file_desc);
    }
    return (i);
}
