#include "shell.h"

/**
 *_eputs - prints an input string
 * @strn: the string to be printed
 * Return: Nothing
 */
void _eputs(char *strn)
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
 * _eputchar - writes the character c to stderr
 * @w: The character to print
 *
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
 * _putfw - writes the character w to given fdd
 * @w: The character to print
 * @fdd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfw(char w, int fdd)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (w == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fdd, buf, i);
i = 0;
}
if (w != BUF_FLUSH)
buf[i++] = w;
return (1);
}

/**
 *_printsfd - prints an input string
 * @str: the string to be printed
 * @fdd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */
int _printsfd(char *str, int fdd)
{
int i = 0;

if (!str)
return (0);
while (*str)
{
i += _printsfd(*str++, fdd);
}
return (i);
}
