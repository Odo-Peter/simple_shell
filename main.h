#ifndef _PRINTF_H_
#define _PRINTF_H_
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* definitions of FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* definitions of SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int _print_handler(const char *fmt, int *i,
		   va_list list, char buffer[], int flags, int width, int precision,
		   int size);

/************ Functions to be used all through *************/

/* Funtions to print chars and strings */
int _char_prints(va_list types, char buffer[],
		 int flags, int width, int precision, int size);
int _print_strs(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int _print_percent(va_list types, char buffer[],
		   int flags, int width, int precision, int size);

/* Functions to print number values */
int _print_int(va_list types, char buffer[],
	       int flags, int width, int precision, int size);
int _print_binary(va_list types, char buffer[],
		  int flags, int width, int precision, int size);
int _print_unsigned(va_list types, char buffer[],
		    int flags, int width, int precision, int size);
int _print_octal(va_list types, char buffer[],
		 int flags, int width, int precision, int size);
int __print_hexadecimal(va_list types, char buffer[],
			int flags, int width, int precision, int size);
int _print_upper_hex(va_list types, char buffer[],
		     int flags, int width, int precision, int size);

int _print_hexa(va_list types, char map_to[],
		char buffer[], int flags, char flag_ch, int width, int precision,
		int size);

/* Function to print non printable chars */
int _print_un_printable(va_list types, char buffer[],
			int flags, int width, int precision, int size);

/* Funcion to print address memory */
int _print_ptr(va_list types, char buffer[],
	       int flags, int width, int precision, int size);

/* Funciotns to handle other specifiers */
int _get_flags(const char *format, int *i);
int _get_width(const char *format, int *i, va_list list);
int _get_precision(const char *format, int *i, va_list list);
int _get_size(const char *format, int *i);

/*Function to print string in reverse*/
int _reverse_print(va_list types, char buffer[],
		   int flags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int print_rot13string(va_list types, char buffer[],
		      int flags, int width, int precision, int size);

/* width handler */
int _write_char(char c, char buffer[],
		int flags, int width, int precision, int size);
int __write_number(int is_positive, int ind, char buffer[],
		   int flags, int width, int precision, int size);
int _write_num(int ind, char bff[], int flags, int width, int precision,
	       int length, char padd, char extra_c);
int _write_ptr(char buffer[], int ind, int length,
	       int width, int flags, char padd, char extra_c, int padd_start);

int _write_unsigned(int is_negative, int ind,
		    char buffer[],
		    int flags, int width, int precision, int size);

/**** Utility functions ****/
int _is_printable(char);
int _hex_code_append(char, char[], int);
int _is_digit(char);

long int _convert_size_num(long int num, int size);
long int _convert_size_unsigned(unsigned long int num, int size);

#endif
