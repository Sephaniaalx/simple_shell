#include "shell.h"

/**
 * add_node - function adds a node to the beginning of the list
 * @head: the address of the pointer to the head node
 * @str: the str field node
 * @num: the node index used by history
 * Return: returns tghe size of list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_to_end - function adds a node to the end of the list
 * @head: the address of the pointer to the head node
 * @str: the str field node
 * @num: the node index used by history
 * Return: returns the size of the list
 */

list_t *add_node_to_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * p_list_str - function prints only the str element of a list_t linked list
 * @b: the pointer to the first node
 * Return: returns the size of the list
 */

size_t p_list_str(const list_t *b)
{
	size_t j = 0;

	while (b)
	{
		_puts(b->str ? b->str : "(nil)");
		_puts("\n");
		b = b->next;
		j++;
	}
	return (j);
}

/**
 * delete_node_at_index - function deletes the node at a given index
 * @head: the adress of the pointer to the first node
 * @index: the index of the node to be deleted
 * Return: returns 1 on success and 0 on failure
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int a = 0;

	if (!head || !*head)
	{
		return (0);
	}

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * f_list - function frees the list of all the nodes of a list
 * @head_ptr: the address of the pointer to the head node
 * Return: returns void
 */

void f_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
	{
		return;
	}
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

