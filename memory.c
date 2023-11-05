#include "shell.h"

/**
 * pointer_free - frees a pointer and NULLs the address
 * @pointer: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int pointer_free(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
