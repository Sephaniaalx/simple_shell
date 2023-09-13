#include "shell.h"

/**
 * _strlen - functions checks the lenght of a string
 * @s: the string whose length is to be checked
 * Return: length of string
 */

int _strlen(char *s)
{
	int j = 0;

	if (!s)
	{
		return (0);
	}
	while (*s++)
	{
		j++;
	}
	return (j);
}

/**
 * _strcmp - function compares two strings
 * @s1: the 1st string
 * @s2: the 2nd string
 * Return: the string compared as an integer
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	if (*s1 == *s2)
	{
		return (0);
	}
	else
	{
		return (*s1 < *s2 ? -1 : 1);
	}
}

/**
 * starts_with - function checks if ned starts with haystack
 * @haystack: the string to search
 * @ned: the substring to find
 * Return: returns the address of next char of haystack or NULL
 */

char *starts_with(const char *haystack, const char *ned)
{
	while (*ned)
	{
		if (*ned++ != *haystack++)
		{
			return (NULL);
		}
	}
	return ((char *)haystack);
}

/**
 * _strcat - function concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 * Return: destination buffer
 */

char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = *src;
	return (ret);
}


