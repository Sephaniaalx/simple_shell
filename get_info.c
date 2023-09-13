#include "shell.h"

/**
 * clear_info - function initializes the info_t structure
 * @info: Poinetr to the info_t structure
 * Return: returns void
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - function initializes the info_t structure
 * @info: Poinetr to the info_t structure
 * @av: the argument vector
 * Return: returns void
 */

void set_info(info_t *info, char **av)
{
	int j = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (j = 0; info->argv && info->argv[j]; j++)
			;
		info->argc = j;

		r_alias(info);
		r_vars(info);
	}
}

/**
 * f_info - function frees the info_t structure
 * @info: Pointer to the info_t structure
 * @all: freeing all the info_t fields if true
 * Return: returns void
 */

void f_info(info_t *info, int all)
{
	f_free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
		{
			free(info->arg);
		}
		if (info->env)
		{
			f_list(&(info->env));
		}
		if (info->history)
		{

			f_list(&(info->history));
		}
		if (info->alias)
		{
			f_list(&(info->alias));
		}
		f_free(info->environ);
			info->environ = NULL;
		b_free((void **)info->cmd_buf);
		{
		if (info->readfd > 2)
			close(info->readfd);
		}
		_putchar(BUF_FLUSH);
	}
}

