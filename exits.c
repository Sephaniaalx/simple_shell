#include "shell.h"

/**
 * _strncpy - this copies a string
 * @src: string source
 * @dest: the destination of the string to be copied
 * @n: the amount of characters to be copied
 * Return: concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
	int k, j;
	char *s = dest;

	k = 0;
	while (src[k] !=  '\0' && k < n - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < n)
	{
		j = k;
		while (j < n)
		{
			dest[j] =  '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - function concatenates two strings
 * @dest: the destination string
 * @src: the source string
 * @n: the maximum nuber of bytes
 * Return: concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] !=  '\0')
	{
		i++;
	}
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
	{
		dest[i] =  '\0';
	}
	return (s);
}

/**
 * _strchr - this locates a character in a string
 * @s: the parsed string
 * @c: the character to search for
 * Return: return(s)
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
		{
			return (s);
		}
	} while (*s++ !=  '\0');

	return (NULL);
}
