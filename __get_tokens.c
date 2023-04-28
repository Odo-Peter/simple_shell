#include "shell.h"

/**
 * **__strtok_one - splits a string into words
 * using delimeters
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings
 * or NULL on failure
 */

char **__strtok_one(char *str, char *d)
{
	int i, j, k, m, num_of_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!__is_delim(str[i], d) && (__is_delim(str[i + 1], d) || !str[i + 1]))
			num_of_words++;

	if (num_of_words == 0)
		return (NULL);
	s = malloc((1 + num_of_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_of_words; j++)
	{
		while (__is_delim(str[i], d))
			i++;
		k = 0;
		while (!__is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **__strtok_two - splits a string into words
 * @str: the input string
 * @d: the delimeter
 * Return: a pointer to an array of strings
 * or NULL on failure
 */
char **__strtok_two(char *str, char d)
{
	int i, j, k, m, num_of_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
		    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			num_of_words++;
	if (num_of_words == 0)
		return (NULL);
	s = malloc((1 + num_of_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_of_words; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
