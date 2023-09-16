#include "shell.h"

/**
 * _env - this prints the current environment of the shell
 * @info: Pointer to the info_t structure
 * Return: Always 0
 */

int _env(info_t *info)
{
	p_list_str(info->env);
	return (0);
}

/**
 * get_env - this gets the value of an environ variable
 * @info: Pointer to the info_t structure
 * @name: the environ variable's name
 * Return: the value of the env
 */

char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
		{
			return (p);
		}
		node = node->next;
	}
	return (NULL);
}

/**
 * set_env - initializes a new environ variable or modifies an existing one
 * @info: Pointer to the info_t structure
 * Return: Always 0
 */

int set_env(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Wrong number of arguments inputed\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
	{
		return (0);
	}
	return (1);
}

/**
 * _unsetenv - This removes an environment variable
 * @info: Pointer to the info_t structure
 * Return: Always 0 on success and 1 on error
 */

int _unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments\n");
		return (1);
	}
	for (i = 1; i < info->argc; i++)
	{
		un_setenv(info, info->argv[i]);
	}
	return (0);
}

/**
 * p_env_list - this populates the env linked list
 * @info: Pointer to the info_t structure
 * Return: Always 0
 */

int p_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
	{
		add_node_to_end(&node, environ[i], 0);
	}
	info->env = node;
	return (0);
}
