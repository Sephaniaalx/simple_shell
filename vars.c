#include "shell.h"

/**
 * is_chain - function checks if current char is a chain delimeter
 * @info: Pointer to the info_t structure
 * @buf: the character buffer
 * @p: the address of the curent position in buffer
 * Return: returns 1 if chain is a delimeter
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t i = *p;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ',')
	{
		buf[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = i;
	return (1);
}

/**
 * check_chain - function check whether there should be a continous chain
 * @info: Pointer to the info_t structure
 * @buf: the char buffer
 * @p: the address of the current position in buf
 * @i: starting position in the buffer
 * @len: the length of the buffer
 * Return: returns void
 */

void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = len;
		}
	}

	*p = k;
}

/**
 * r_alias - function replaces an aliase in the tokenized string
 * @info: Pointer to the info_t structure
 * Return: returns 1 on success
 */

int r_alias(info_t *info)
{
	int j;
	list_t *node;
	char *p;

	for (j = 0; j < 10; j++)
	{
		node = node_start_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * r_vars - function replaces vars in the tokenized string
 * @info: Pointer to the info_t structure
 * Return: returns 1 on success
 */

int r_vars(info_t *info)
{
	int j = 0;
	list_t *node;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!_strcmp(info->argv[j], "$?"))
		{
			r_string(&(info->argv[j]),
					_strdup(c_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[j], "$$"))
		{
			r_string(&(info->argv[j]),
					_strdup(c_number(getpid(), 10, 0)));
			continue;
		}
		node = node_start_with(info->env, &info->argv[j][1], '=');
		if (node)
		{
			r_string(&(info->argv[j]), _strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		r_string(&info->argv[j], _strdup(""));

	}
	return (0);
}

/**
 * r_string - function replaces string
 * @old: the address of an old string
 * @new: the address of the new string
 * Return: returns 1 on success
 */

int r_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}


