#include "shell.h"

/**
 * __h_shell - main shell loop
 * @info: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success
 * 1 on error, or error code eg 126
 */
int __h_shell(info_t *info, char **argv)
{
	ssize_t r = 0;
	int builtin_return = 0;

	while (r != -1 && builtin_return != -2)
	{
		clear_info(info);
		if (__is_interactive(info))
			_puts("Konichiwa :)$ ");
		__error_putchar(BUFFER_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, argv);
			builtin_return = __find_builtins(info);
			if (builtin_return == -1)
				__find_commands(info);
		}
		else if (__is_interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	__write_history(info);
	free_info(info, 1);
	if (!__is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_return == -2)
	{
		if (info->error_number == -1)
			exit(info->status);
		exit(info->error_number);
	}
	return (builtin_return);
}

/**
 * __find_builtins - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * 2 if builtin signals exit()
 */
int __find_builtins(info_t *info)
{
	int i, builtin_return_val = -1;
	builtin_t builtin_table_fmt[] = {
		{"exit", __exit},
		{"env", __env},
		{"help", __help},
		{"history", __history},
		{"setenv", __setenv},
		{"unsetenv", __unsetenv},
		{"cd", __cd},
		{"alias", __alias},
		{NULL, NULL}};

	for (i = 0; builtin_table_fmt[i].type; i++)
		if (_strcmp(info->argv[0], builtin_table_fmt[i].type) == 0)
		{
			info->line_count++;
			builtin_return_val = builtin_table_fmt[i].func(info);
			break;
		}
	return (builtin_return_val);
}

/**
 * __find_commands - finds a command in PATH
 * @info: the parameter & return info struct
 * Return: void function
 */
void __find_commands(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!__is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;
	path = __path_finder(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		__fork_command(info);
	}
	else
	{
		if ((__is_interactive(info) || _getenv(info, "PATH=") ||
		     info->argv[0][0] == '/') && __is_command(info, info->argv[0]))
			__fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			__p_error(info, "not found\n");
		}
	}
}

/**
 * __fork_command - forks a an execution thread
 * to run commands
 * @info: the parameter & return info struct
 * Return: void function
 */
void __fork_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				__p_error(info, "Permission denied\n");
		}
	}
}
