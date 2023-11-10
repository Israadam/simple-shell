#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @parg: the parameter struct
 * @buf: the char buffer
 * @a: address of current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *parg, char *buf, size_t *a)
{
size_t j = *a;

if (buf[j] == '|' && buf[j + 1] == '|')
{
buf[j] = 0;
j++;
parg->cmd_buf_type = CMD_OR;
}
else if (buf[j] == '&' && buf[j + 1] == '&')
{
buf[j] = 0;
j++;
parg->cmd_buf_type = CMD_AND;
}
else if (buf[j] == ';') /* found end of this command */
{
buf[j] = 0; /* replace semicolon with null */
parg->cmd_buf_type = CMD_CHAIN;
}
else
return (0);
*a = j;
return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @parg: the parameter struct
 * @buf: the char buffer
 * @a: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void check_chain(info_t *parg, char *buf, size_t *a, size_t i, size_t len)
{
size_t j = *a;

if (parg->cmd_buf_type == CMD_AND)
{
if (parg->status)
{
buf[i] = 0;
j = len;
}
}
if (parg->cmd_buf_type == CMD_OR)
{
if (!parg->status)
{
buf[i] = 0;
j = len;
}
}

*a = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @parg: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *parg)
{
int i;
list_t *node;
char *p;

for (i = 0; i < 10; i++)
{
node = node_starts_with(parg->alias, parg->argv[0], '=');
if (!node)
return (0);
free(parg->argv[0]);
p = _strchr(node->str, '=');
if (!p)
return (0);
p = _strdup(p + 1);
if (!p)
return (0);
parg->argv[0] = p;
}
return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @parg: the parameter struct
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *parg)
{
int i = 0;
list_t *node;

for (i = 0; parg->argv[i]; i++)
{
if (parg->argv[i][0] != '$' || !parg->argv[i][1])
continue;

if (!_strcmp(parg->argv[i], "$?"))
{
replace_string(&(parg->argv[i]),
_strdup(convert_number(parg->status, 10, 0)));
continue;
}
if (!_strcmp(parg->argv[i], "$$"))
{
replace_string(&(parg->argv[i]),
_strdup(convert_number(getpid(), 10, 0)));
continue;
}
node = node_starts_with(parg->env, &parg->argv[i][1], '=');
if (node)
{
replace_string(&(parg->argv[i]),
_strdup(_strchr(node->str, '=') + 1));
continue;
}
replace_string(&parg->argv[i], _strdup(""));

}
return (0);
}

/**
 * replaces_string - replaces string
 * @old: address of the old string
 * @nw: new string
 * Return: 1 if replaced, 0 otherwise
 */
int replaces_string(char **old, char *nw)
{
free(*old);
*old = nw;
return (1);
}
