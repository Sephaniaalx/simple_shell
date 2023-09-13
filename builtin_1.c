#include "shell.h"

/**
 * _history - Display the command history with line numbers
 * @info: Pointer to the info_t structure
 * Return: Always 0
 */
int _history(info_t *info)
{
	p_list(info->history);
	return (0);
}
/**
 * unset_alias - Unset an alias
 * @info: Pointer to the info_t structure
 * @str: the alias string to unset
 * Return: Always 0
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias), get_node_index(info->alias,
				node_start_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}
/**
 * set_alias - this sets an alias to a string
 * @info: Pointer to the info_t structure
 * @str: the string's alias
 * Return: Always 0
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_to_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - this prints an alias of a string
 * @node: this is the alias node
 * Return: Always 0
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
		{
			_putchar(*a);
			_putchar('\\');
			_puts(p + 1);
			_puts("\n");
			return (0);
		}
	}
	return (1);
}

/**
* _alias - Display or manages shell aliases
* @info: Poinetr to the info_t structure
*
* Return: Always 0
*/
int _alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_start_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
