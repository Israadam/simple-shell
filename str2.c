#include "shell.h"

/**
 * _strdup - duplicates a string
 * @dup: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *dup)
{
	int length = 0;
	char *i;

	if (dup == NULL)
		return (NULL);
	while (*dup++)
		length++;
	i = malloc(sizeof(char) * (length + 1));
	if (!i)
		return (NULL);
	for (length++; length--;)
		i[length] = *--dup;
	return (i);
}
/**
 * _strcpy - copies a string
 * @dest: the destination
 * @stc: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *stc)
{
	int i = 0;

	if (dest == stc || stc == 0)
		return (dest);
	while (stc[i])
	{
		dest[i] = stc[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}


/**
 * _putchar - writes the character c to stdout
 * @ch: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}

/**
 *_puts - prints an input string
 *@s: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		_putchar(s[i]);
		i++;
	}
}
