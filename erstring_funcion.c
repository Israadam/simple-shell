#include "shell.h"
/**
 * _eputchar - writes the character h to stderr
 * @h: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char h)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	if (h == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (h != BUF_FLUSH)
		buf[i++] = h;
	return (1);
}

/**
 *_putsfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;
	
	if (!str)
		return (0);
	
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}
/**
 *_eputs - prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */
void _eputs(char *str)
{
        int i = 0;

        if (!str)
                return;

        while (str[i] != '\0')
        {
                _eputchar(str[i]);
                i++;
        }
}
/**
 * _putfd - writes the character b to given fd
 * @b: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char b, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	
	if (b == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (b != BUF_FLUSH)
		buf[i++] = b;
	return (1);
}
