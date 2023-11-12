#include "shell.h"

/**
 * _historylst - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _historylst(info_t *info)
{
print_list(info->history);
return (0);
}

/**
<<<<<<< HEAD
 * unsetalias - sets alias to string
 * @parg: parameter struct
=======
 * unset_alias - sets alias to string
 * @info: parameter struct
>>>>>>> c05c887373f6021e6b6001093d9b9e183d1bf6f8
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
<<<<<<< HEAD
int unsetalias(info_t *parg, char *str)
=======
int unset_alias(info_t *info, char *str)
>>>>>>> c05c887373f6021e6b6001093d9b9e183d1bf6f8
{
char *p, c;
int ret;
p = _strchr(str, '=');
if (!p)
return (1);
c = *p;
*p = 0;
ret = delete_node_at_index(&(info->alias),
get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
*p = c;
return (ret);
}

<<<<<<< HEAD
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
=======

>>>>>>> c05c887373f6021e6b6001093d9b9e183d1bf6f8

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
<<<<<<< HEAD
 * _my_alias - mimics the alias builtin (man alias)
 * @parg: Structure containing potential arguments. works to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _my_alias(info_t *parg)
=======
 * _mmalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _mmalias(info_t *info)
>>>>>>> c05c887373f6021e6b6001093d9b9e183d1bf6f8
{
int i = 0;
char *p = NULL;
list_t *node = NULL;

if (info->argc == 1)
{
node = info->alias;
while (node)
{
printalias(node);
node = node->next;
}
return (0);
}
for (i = 1; info->argv[i]; i++)
{
p = _strchr(info->argv[i], '=');
if (p)
<<<<<<< HEAD
setalias(parg, parg->argv[i]);
else
printalias(start_with(parg->alias, parg->argv[i], '='));
=======
set_alias(info, info->argv[i]);
else
print_alias(node_starts_with(info->alias, info->argv[i], '='));
>>>>>>> c05c887373f6021e6b6001093d9b9e183d1bf6f8
}

return (0);
}


/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
char *p;
p = _strchr(str, '=');
if (!p)
return (1);
if (!*++p)
return (unset_alias(info, str));
unset_alias(info, str);
return (add_node_end(&(info->alias), str, 0) == NULL);
}
