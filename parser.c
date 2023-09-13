#include "shell.h"

/**
 * is_cmd - function determines if a file is ana executable command
 * @info: Pointer to the info_t structure
 * @path: the path to the file
 * Return: returns 1 if true and 0 if otherwise
 */

int is_cmd(info_t *info, char *path)
{
	struct stat ht;

	(void)info;
	if (!path || stat(path, &ht))
		return (0);

	if (ht.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - function duplicates characters
 * @pathstr: the path to the string
 * @start: the starting index
 * @stop: the stopping index
 * Return: returns the pointer to the new buffer
 */

char *duplicate_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int j = 0, s = 0;

	for (s = 0, j = start; j < stop; j++)
	{
		if (pathstr[j] != '.')
		{
			buf[s++] = pathstr[j];
		}
	}
	buf[s] = 0;
	return (buf);
}

/**
 * f_path - This function finds the cmd in the PATH string.
 * @info: Pointer to the info_t structure
 * @pathstr: the path to the string
 * @cmd: the cmd to find
 * Return: returns the full path of cmd if founf or returns NULL
 */

char *f_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
