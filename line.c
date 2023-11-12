#include "shell.h"

/**
 * input_buff - buffers chained commands
 * @parg: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: bytes read
 */
ssize_t input_buff(info_t *parg, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintcntrl);
#if USE_GETNXTLINE
		r = getnxtline(buf, &len_p, stdin);
#else
		r = _getnxtline(parg, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			parg->linecount_flag = 1;
			rm_comments(*buf);
			build_history_link(parg, *buf, parg->histcount++);
			{
				*len = r;
				parg->cmd_buf = buf;
			}
		}
	}
	return (r);
}


/**
 * _getnxtline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptp: address of pointer to buffer, preallocated or NULL
 * @size: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getnxtline(info_t *info, char **ptp, size_t *size)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptp;

	if (p && size)
		s = *size;

	if (i == len)
		i = len = 0;
	r = read_buffer(info, buf, &len);

	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = realloc_mem(p, s, s ? s + k : k + 1);

	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);

	else
		_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;

	if (size)
		*size = s;
	*ptp = p;
	return (s);
}


/**
 * set_input - gets a line minus the newline
 * @parg: parameter struct
 * Return: bytes read
 */
ssize_t set_input(info_t *parg)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(parg->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buff(parg, &buf, &len);

	if (r == -1) /* EOF */
		return (-1);

	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buf + i; /* get pointer for return */
		test_chain(parg, buf, &j, i, len);

		while (j < len) /* iterate to semicolon or end */
		{
			if (_chain(parg, buf, &j))
				break;
			j++;
		}
		i = j + 1; /* increment past nulled ';'' */

		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			parg->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf;
	return (r);
/**
 * sigintcntrl - blocks ctrl-C
 * @sign_num: the signal number
 * Return: void
 */
void sigintcntrl(__attribute__((unused))int sign_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @s: size
 * Return: r
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *s)
{
        ssize_t r = 0;

        if (*s)
                return (0);
        r = read(parg->readfd, buf, READ_BUF_SIZE);

        if (r >= 0)
                *s = r;
        return (r);
}
