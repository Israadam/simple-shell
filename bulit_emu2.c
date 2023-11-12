#include "shell.h"

/**
 * _histlst - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @parg: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 *  Return: Always 0
 */
int _histlst(info_t *parg)
{
printlist(parg->history);
return (0);
}

/**
 * unsetalias - sets alias to string
 * @parg: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unsetalias(info_t *parg, char *str)
{
char *p, c;
int ret;

p = _strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_at_given_index(&(parg->alias),
node_index(parg->alias,starts_with(parg->alias, str, -1)));
*p = c;
return (ret);
}

/**
 * setalias - sets alias to string
 * @parg: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int setalias(info_t *parg, char *str)
{
char *p;

p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(parg, str));

unsetalias(parg, str);
return (add_node_list(&(parg->alias), str, 0) == NULL);
}

/**
 * printalias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int printalias(list_t *node)
{
char *p = NULL, *a = NULL;

if (node)
{
p = _strchr(node->str, '=');
for (a = node->str; a <= p; a++)
_putchar(*a);
_putchar('\'');
_puts(p + 1);
_puts("'\n");
return (0);
}
return (1);
}

/**
 * _my_alias - mimics the alias builtin (man alias)
 * @parg: Structure containing potential arguments. works to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_alias(info_t *parg)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;

if (parg->argc == 1)
{
node = parg->alias;
while (node)
{
printalias(node);
node = node->next;
}
return (0);
}
for (i = 1; parg->argv[i]; i++)
{
p = _strchr(parg->argv[i], '=');
if (p)
setalias(parg, parg->argv[i]);
else
printalias(start_with(parg->alias, parg->argv[i], '='));
}
return (0);
}
