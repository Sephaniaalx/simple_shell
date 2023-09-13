#include "shell.h"

/**
 * list_len - function determines the length of the linked list
 * @m: the pointer to the first node
 * Return: returns the size of the list
 */

size_t list_len(const list_t *m)
{
	size_t j = 0;

	while (m)
	{
		m = m->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - function returns an array of strings of the list->str
 * @head: the pointer to the first node
 * Return: returns an array of strings
 */

char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strns;
	char *str;

	if (!head || !i)
		return (NULL);
	strns = malloc(sizeof(char *) * (i + 1));

	if (!strns)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strns[j]);
			free(strns);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strns[i] = str;
	}
	strns[i] = NULL;
	return (strns);
}

/**
 * p_list - function prints all elements of a list_t linked list
 * @m: the pointer to the first node
 * Return: returns the size of the list
 */

size_t p_list(const list_t *m)
{
	size_t j = 0;

	while (m)
	{
		_puts(c_number(m->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(m->str ? m->str : "(nil)");
		_puts("\n");
		m = m->next;
		j++;
	}
	return (j);
}

/**
 * node_start_with - function returns the node whose string starts with prefix
 * @node: the poinetr to the list head
 * @prefix: the string match
 * @c: the next character that comes after the prefix match
 * Return: returns the match node or a null
 */

list_t *node_start_with(list_t *node, char *prefix, char c)
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
 * get_node_index - function gets the index of a node
 * @head: the poinetr to the list head
 * @node: the pointer to the node
 * Return: returns the index of node or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
		{
			return (j);
		}
		head = head->next;
		j++;
	}
	return (-1);
}

