#include "shell.h"

/**
 * exit_ - this exits the simple shell
 * @info: Pointer to the info_t structure
 * Return: exits with a given exit status
 * if info argv[0] != "exit" returns 0
 */

int exit_(info_t *info)
{
	int exit_check;

	if (info->argv[1])
	{
		exit_check = err_atoi(info->argv[1]);
		if (exit_check == -1)
		{
			info->status = 2;
			p_error(info, "Wrong number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = err_atoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _cd - changes the current directory
 * @info: Pointer to the info_t structure
 * Return: Always 0
 */

int _cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
	{
		chdir_ret = chdir(info->argv[1]);
	}
	if (chdir_ret == -1)
	{
		p_error(info, "Wrong command for cd");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", get_env(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help - changes the current directory
 * @info: Pointer to the info_t structure
 * Return: Always 0
 */

int help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("Calls work. Function not implemented yet \n");
	if (0)
	{
		_puts(*arg_array);
	}
	return (0);
}
