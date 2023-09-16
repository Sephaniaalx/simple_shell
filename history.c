#include "shell.h"

/**
 * get_hist_file - function gets the historyfile
 * @info: Pointer to the info_t structure
 * Return: Return the allocated string containing the history file
 */

char *get_hist_file(info_t *info)
{
	char *buf, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
	{
		return (NULL);
	}
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
	{
		return (NULL);
	}
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist - function creates a file or appends to an existing file
 * @info: Pointer to the info_t structure
 * Return: returns 1 on success and -1 if otherwise
 */

int write_hist(info_t *info)
{
	ssize_t fd;
	char *filename = get_hist_file(info);
	list_t *node = NULL;

	if (!filename)
	{
		return (-1);
	}

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
	{
		return (-1);
	}
	for (node = info->history; node; node = node->next)
	{
		puts_fd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_hist - function reads history from a file
 * @info: Pointer to the info_t structure
 * Return: returns histcount on success
 */

int read_hist(info_t *info)
{
	int a, last = 0, linecount = 0;

	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_hist_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (a = 0; a < fsize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			build_hist_list(info, buf + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		build_hist_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	re_number_hist(info);
	return (info->histcount);
}

/**
 * build_hist_list - function adds entry to a histry linked list
 * @info: Pointer to the info_t structure
 * @buf: the buffer to be added
 * @linecount: the linecount of the history
 * Return: Always 0
 */

int build_hist_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
	{
		node = info->history;
	}
	add_node_to_end(&node, buf, linecount);

	if (!info->history)
	{
		info->history = node;
	}
	return (0);
}

/**
 * re_number_hist - function renumbers the history linked list
 * @info: Poiter to the info_t structure
 * Return: Returns the new histcount
 */

int re_number_hist(info_t *info)
{
	list_t *node = info->history;
	int j = 0;

	while (node)
	{
		node->num = j++;
		node = node->next;
	}
	return (info->histcount = j);
}


