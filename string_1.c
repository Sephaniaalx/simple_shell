#include "shell.h"

/**
 * _strcpy - function copies a string
 * @src: the buffer source
 * @dest: the dstination buffer
 * Return: a copied string
 */

char *_strcpy(char *dest, char *src)
{
	int j = 0;

	if (dest == src || src == 0)
	{
		return (dest);
	}
	while (src[j])
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = 0;
	return (dest);
}

/**
 * _strdup - function duplicates a string
 * @s: the string to duplicate
 * Return: the duplicated string
 */

char *_strdup(const char *s)
{
	int length = 0;
	char *ret;

	if (s == NULL)
	{
		return (NULL);
	}
	while (*s++)
	{
		length++;
	}
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
	{
		return (NULL);
	}
	for (length++; length--;)
	{
		ret[length] = *--s;
	}
	return (ret);
}

/**
 * _puts - function prints an input string
 * @s: the string to be printed
 * Return: returns void
 */

void _puts(char *s)
{
	int j = 0;

	if (!s)
	{
		return;
	}
	while (s[j] != '\0')
	{
		_putchar(s[j]);
		j++;
	}
}

/**
 * _putchar - function writes the character c to the stdout
 * @c: the character to be printed
 * Return: returns 1 on success and -1 on error
 */

int _putchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[j++] = c;
	}
	return (1);
}

