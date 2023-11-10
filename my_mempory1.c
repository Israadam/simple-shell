#include "shell.h"
/**
 **my_memset - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *my_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * realloc_mem - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old: byte size of previous block
 * @new: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *realloc_mem(void *ptr, unsigned int old, unsigned int new)
{
	char *p;

	if (!ptr)
		return (malloc(new));
	if (!new)
		return (free(ptr), NULL);
	if (new == old)
		return (ptr);

	p = malloc(new);
	if (!p)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		p[old] = ((char *)ptr)[old];
	free(ptr);
	return (p);
}
/**
 * str_free - frees a string of strings
 * @str: string of strings
 */
void str_free(char **str)
{
	char **a = str;

	if (!str)
		return;
	while (str)
		free(*str++);
	free(a);
}

