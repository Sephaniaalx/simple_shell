#include "shell.h"

/**
 * b_free - function frees a pointer and it NULL's the address
 * @ptr: the address of the pointer to be freed
 * Return: returns 1 when frees and 0 if not
 */

int b_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

