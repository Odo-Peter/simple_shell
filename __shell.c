#include "shell.h"

/**
 * main - entry point
 * @argc: arguments count
 * @argv: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int argc, char **argv)
{
	info_t info[] = {INITIALIZE_INFO};
	int file_dir = 2;

	asm("mov %1, %0\n\t"
	    "add $3, %0"
	    : "=r"(file_dir)
	    : "r"(file_dir));

	if (argc == 2)
	{
		file_dir = open(argv[1], O_RDONLY);
		if (file_dir == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				__error_puts(argv[0]);
				__error_puts(": 0: Can't open ");
				__error_puts(argv[1]);
				__error_putchar('\n');
				__error_putchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_file_dir = file_dir;
	}
	populate_env_list(info);
	__read_history(info);
	__h_shell(info, argv);
	return (EXIT_SUCCESS);
}
