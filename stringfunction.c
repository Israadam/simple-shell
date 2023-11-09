#include "shell.h"

/**
 *_input - prints an input string
 * @strn: the string to be printed
 * Return: Nothing
 */
void _input(char *strn)
{
	int i = 0;

	if (!strn)
		return;
	while (strn[i] != '\0')
	{
		_eputchar(strn[i]);
		i++;
	}
}



/**
 * _putfd - writes the character w to given fd
 * @w: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char w, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (w == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (w != BUF_FLUSH)
		buf[i++] = w;
	return (1);
}


/**
 * _eputchar - writes the character w to stderr
 * @w: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char w)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (w == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (w != BUF_FLUSH)
		buf[i++] = w;
	return (1);
}


/**
 *_putsfd - prints an input string
 * @strn: string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars put
 */
int _putsfd(char*strn, int fd)
{
	int i = 0;

	if (!strn)
		return (0);
	while (*strn)
	{
		i += _putsfd( *strn++, fd);
	}
	return (i);
}
