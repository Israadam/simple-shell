#include "shell.h"

/**
 *_eputsd - prints an input string
 * @strg: the string to be printed
 *
 * Return: Nothing
 */
void _eputsd(char *strg)
{
int i = 0;
if (!strg)
return;
while (strg[i] != '\0')
{
_eputchar(strg[i]);
i++;
}
}

/**
 *_putstrng - prints an input string
 * @stng: string to be printed
 * @fds:filedescriptor to write
 * Return: the number of chars put
 */
int _putstrng(char *stng, int fds)
{
int i = 0;
if (!stng)
return (0);
while (*stng)
{
i += _putfd(*stng++, fds);
}
return (i);
}

/**
 * _eputchar - writes the character w  to stderr
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
 * _putfd - writes the character s to given fs
 * @s: The character to print
 * @fs: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char s, int fs)
{
static int i;
static char buf[WRITE_BUF_SIZE];

if (s == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(fs, buf, i);
i = 0;
}
if (s != BUF_FLUSH)
buf[i++] = s;
return (1);
}
