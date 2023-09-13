#include "shell.h"

/**
 * _eputs - the printer of an input string
 * @str: the string that is to be printed
 * Return: Returns nothing
 */

void _eputs(char *str)
{
	int i = 0;

	if (!str)
	{
		return;
	}
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - this writes the charcter c to stderr
 * @c: the character to be printed
 * Return: 1 on success and -1 on error
 */

int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}
	return (1);
}

/**
 * put_fd - writes the character c to a given fd
 * @c: the character to be printed
 * @fd: file descriptor to be written to
 * Return: Returns 1 on success and -1 on error
 */

int put_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}
	return (1);
}

/**
 * puts_fd - this prints an input string
 * @str: the string to be printed
 * @fd: the file descriptor to be written to
 * Return: Returns the number characters
 */

int puts_fd(char *str, int fd)
{
	int i = 0;

	if (!str)
	{
		return (0);
	}
	while (*str)
	{
		i += put_fd(*str++, fd);
	}
	return (i);
}
