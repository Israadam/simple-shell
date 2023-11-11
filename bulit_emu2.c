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
 * unset_alias - sets alias to string
 * @parg: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *parg, char *str)
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
 * set_alias - sets alias to string
 * @parg: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *parg, char *str)
{
char *p;

p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(parg, str));

unset_alias(parg, str);
return (add_node_list(&(parg->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
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
 * _myalias - mimics the alias builtin (man alias)
 * @parg: Structure containing potential arguments. works to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *parg)
{
int i = 0;
char *p = NULL;
list_t *node = NULL;

if (parg->argc == 1)
{
node = parg->alias;
while (node)
{
print_alias(node);
node = node->next;
}
return (0);
}
for (i = 1; parg->argv[i]; i++)
{
p = _strchr(parg->argv[i], '=');
if (p)
set_alias(parg, parg->argv[i]);
else
print_alias(starts_with(parg->alias, parg->argv[i], '='));
}
return (0);
}
