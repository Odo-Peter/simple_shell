#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers is in given string
 * else, converted number is returned
 * otherwise -1 on error
 */
int _erratoi(char *str)
{
    int i = 0;
    unsigned long int result = 0;

    if (*str == '+')
        str++;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            result *= 10;
            result += (str[i] - '0');
            if (result > INT_MAX)
                return (-1);
        }
        else
            return (-1);
    }
    return (result);
}

/**
 * __p_error - prints an error message
 * @info: the params from info struct
 * @error_str: string containing specified error type
 * Return: void function
 */
void __p_error(info_t *info, char *error_str)
{
    __error_puts(info->file_name);
    __error_puts(": ");
    print_d(info->line_count, STDERR_FILENO);
    __error_puts(": ");
    __error_puts(info->argv[0]);
    __error_puts(": ");
    __error_puts(error_str);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @file_desc: the file descriptor to write to
 * Return: number of characters
 */
int print_d(int input, int file_desc)
{
    int (*__putchar)(char) = _putchar;
    int i, count = 0;
    unsigned int _absolute_, current;

    if (file_desc == STDERR_FILENO)
        __putchar = __error_putchar;
    if (input < 0)
    {
        _absolute_ = -input;
        __putchar('-');
        count++;
    }
    else
        _absolute_ = input;
    current = _absolute_;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (_absolute_ / i)
        {
            __putchar('0' + current / i);
            count++;
        }
        current %= i;
    }
    __putchar('0' + current);
    count++;

    return (count);
}

/**
 * convert_number - converter function, a mock of C itoa
 * @num: number
 * @base: base
 * @flags: argument flags recieved
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
    static char *char_array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }
    char_array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = char_array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return (ptr);
}

/**
 * remove_comments - function replaces
 * first instance of '#' with '\0'
 * @buf: address of the string to modify
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
    int i;

    for (i = 0; buf[i] != '\0'; i++)
        if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
        {
            buf[i] = '\0';
            break;
        }
}
