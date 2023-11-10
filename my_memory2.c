#include "shell.h"

/**
 * free_pointer - frees a pointer and NULLs the address
 * @poi: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_pointer(void **poi)
{
	if (poi && *poi)
	{
		free(*poi);
		*poi = NULL;
		return (1);
	}
	return (0);
}
