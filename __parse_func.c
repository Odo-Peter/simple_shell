#include "shell.h"

/**
 * __is_command - determines if a file
 * is an executable command or not
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int __is_command(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * __duplicate_chars - duplicates characters
 * @path_string: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *__duplicate_chars(char *path_string, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path_string[i] != ':')
			buf[k++] = path_string[i];
	buf[k] = 0;
	return (buf);
}

/**
 * __path_finder - finds a given cmd in the PATH string
 * @info: the info struct
 * @path_string: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *__path_finder(info_t *info, char *path_string, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!path_string)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (__is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_string[i] || path_string[i] == ':')
		{
			path = __duplicate_chars(path_string, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (__is_command(info, path))
				return (path);
			if (!path_string[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
