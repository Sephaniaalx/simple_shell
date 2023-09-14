#include "shell.h"

/**
 * _memset - function fills the memory with a constant byte
 * @a: the pointer to the memory area
 * @b: the byte to fill *a with
 * @c: the amount of bytes to be filled
 * Return: retuns (a) which is a pointer to the memory area
 */

char *_memset(char *a, char b, unsigned int c)
{
	unsigned int j;

	for (j = 0; j < c; j++)
	{
		a[j] = b;
	}
	return (a);
}

/**
 * f_free - function frees a string of strings
 * @pp: the string of strings
 * Return: returns void
 */

void f_free(char **pp)
{
	char **d = pp;

	if (!pp)
	{
		return;
	}
	while (*pp)
	{
		free(*pp++);
	}
	free(d);
}


/**
 * _realloc - function reallocates a block of memory
 * @ptr: a poinetr to the previous block of malloc
 * @old_size: the byte size of the previous block
 * @new_size: the byte size of the new block
 * Return: returns the pointer to the old block
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
	{
		return (malloc(new_size));
	}
	if (!new_size)
	{
		return (free(ptr), NULL);
	}
	if (new_size == old_size)
	{
		return (ptr);
	}

	p = malloc(new_size);
	if (!p)
	{
		return (NULL);
	}

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
	{
		p[old_size] = ((char *)ptr)[old_size];
	}
	free(ptr);
	return (p);
}

