#include "shell.h"

/**
 * err_atoi - this converts a string to an interger
 * @s: the string to be converted into an integer
 * Return: 0 on success and -1 on error
 */

int err_atoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
	{
		s++;
	}
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
	}
	return (result);
}

/**
 * p_error - this prints an error message
 * @info: Pointer to the info_t structure
 * @estr: string containing a specified error type
 * Return: 0 on success and -1 on error
 */

void p_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_decimal - this prints a decimal number in base 10
 * @input: the input to print
 * @fd: the file descriptor to be written to
 * Return: returns the number characters that is printed
 */

int print_decimal(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
	{
		__putchar = _eputchar;
	}
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
	{
		_abs_ = input;
	}
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * c_number - this a converter, a clone of itoa
 * @num: a number
 * @base: a base
 * @flags: the argument flags
 * Return: returns a string
 */

char *c_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
	{
		*--ptr = sign;
	}
	return (ptr);
}

/**
 * r_comments - this replaces the first instance of '#' with '\0'
 * @buf: address of the string to be modified
 * Return: Always 0
 */

void r_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
	{
		if (buf[j] == '#' && (!j  || buf[j - 1] == ' '))
		{
			buf[j] =   '\0';
			break;
		}
	}
}
