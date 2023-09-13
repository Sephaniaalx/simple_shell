#include "shell.h"

/**
 * shell_loop - this function is the maun shell loop
 * @info: Pointer to the info_t structure
 * @av: the argument vector from the main
 * Return: returns 0 on success and 1 on error
 */

int shell_loop(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = f_builtin(info);
			if (builtin_ret == -1)
				f_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		f_info(info, 0);
	}
	write_hist(info);
	f_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * f_builtin - function finds a builtin command
 * @info: Pointer to the info_t structure
 * Return: returns 0 if builtin is executed and 0 if not
 */

int f_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtinbl[] = {
		{"exit", exit_},
		{"env", _env},
		{"help", help},
		{"history", _history},
		{"setenv", set_env},
		{"unsetenv", _unsetenv},
		{"cd", _cd},
		{"alias", _alias},
		{NULL, NULL}
	};

	for (i = 0; builtinbl[i].type; i++)
		if (_strcmp(info->argv[0], builtinbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtinbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * f_cmd - function finds a command in path
 * @info: Pointer to the info_t structure
 * Return: returns void
 */

void f_cmd(info_t *info)
{
	char *path = NULL;
	int i, j;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, j = 0; info->arg[i]; i++)
		if (!is_delimeter(info->arg[i], " \t\n"))
			j++;
	if (!j)
		return;

	path = f_path(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{

			if ((interactive(info) || get_env(info, "PATH=")
						 || info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
				fork_cmd(info);
			else if (*(info->arg) != '\n')
			{
				info->status = 127;
				p_error(info, "could not be found\n");
			}
	}
}

/**
 * fork_cmd - function forks an executable thread to run cmd
 * @info: Pointer to the info_t structure
 * Return: returns void
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error occurred");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			f_info(info, 1);
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
				p_error(info, "Can't access\n");
		}
	}
}

