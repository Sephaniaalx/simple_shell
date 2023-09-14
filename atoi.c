#include "shell.h"

/**
 * interactive - returns true if the shell is in interactive mode
 * @info: the struct address
 * Return: 1 if it is in interactive mood and 0 if otherwise
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delimeter - checks if character is a delimeter
 * @c: the character to be checked
 * @delim: the delimeter string
 * Return: 1 if its true and 0 if its false
 */

int is_delimeter(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
		{
			return (1);
		}
	}
	return (0);
}

/**
 * is_alpha - checks if a character is alphabetic
 * @c: the character to be inputed
 * Return: 1 if c is an alphabet and 0 if c is not an alphabet
 */

int is_alpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/**
 * atoi_ - converts a string to an integer
 * @s: the string to be converted into an integer
 * Return: 0 if there are no numbers in the string
 */

int atoi_(char *s)
{
	int i, sign = 1, flag = 0, output;

	unsigned int result = 0;

	for (i = 0; s[i] !=  '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
		{
			sign *= -1;
		}
		if (s[i] >=  '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] -  '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
	}

	if (sign == -1)
	{
		output = -result;
	}
	else
	{
		output = result;
	}

	return (output);
}
