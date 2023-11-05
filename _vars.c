#include "shell.h"

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}
/**
 *test_chain - test if current char in buffer is a chain delimeter
 * @inf: the parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int test_chain(info_t *inf, char *buff, size_t *ptr)
{
	size_t j = *ptr;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buff[j] == ';') /* found end of this command */
	{
		buff[j] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}


/**
 * replacing_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replacing_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
/**
 *alias_replace - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int alias_replace(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = start_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replacing_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replacing_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replacing_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replacing_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = start_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replacing_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replacing_string(&info->argv[i], _strdup(""));

	}
	return (0);
}
