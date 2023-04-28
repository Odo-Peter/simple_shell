#include "shell.h"

/**
 * list_len - determines length of linked list
 * @head_ptr: pointer to first node
 * Return: size of list
 */
size_t list_len(const list_t *head_ptr)
{
	size_t i = 0;

	while (head_ptr)
	{
		head_ptr = head_ptr->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head_node: pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *head_node)
{
	list_t *node = head_node;
	size_t i = list_len(head_node), j;
	char **strs;
	char *str;

	if (!head_node || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @head_ptr: pointer to first node
 * Return: size of the list
 */
size_t print_list(const list_t *head_ptr)
{
	size_t i = 0;

	while (head_ptr)
	{
		_puts(convert_number(head_ptr->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head_ptr->str ? head_ptr->str : "(nil)");
		_puts("\n");
		head_ptr = head_ptr->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head_node
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_at_index - gets the index of a node
 * @head_ptr: pointer to list head
 * @node_ptr: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_at_index(list_t *head_ptr, list_t *node_ptr)
{
	size_t i = 0;

	while (head_ptr)
	{
		if (head_ptr == node_ptr)
			return (i);
		head_ptr = head_ptr->next;
		i++;
	}
	return (-1);
}
