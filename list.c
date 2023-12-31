#include "shell.h"


/**
 * free_node - frees all nodes of a list
 * @head_pointr: address of pointer to head node
 * Return: void
 */
void free_node(list_t **head_pointr)
{
list_t *node, *next_node, *head;
if (!head_pointr || !*head_pointr)
return;
head = *head_pointr;
node = head;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}
*head_pointr = NULL;
}

/**
 * add_list - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 * Return: size of list
 */
list_t *add_list(list_t **head, const char *str, int num)
{
list_t *new_head;
if (!head)
return (NULL);
new_head = malloc(sizeof(list_t));
if (!new_head)
return (NULL);
memset((void *)new_head, 0, sizeof(list_t));
new_head->num = num;
if (str)
{
new_head->str = _strdup(str);
if (!new_head->str)
{
free(new_head);
return (NULL);
}
}
new_head->next = *head;
*head = new_head;
return (new_head);
}

/**
 * end_list - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_t *end_list(list_t **head, const char *str, int num)
{
list_t *new_node, *node;

if (!head)
return (NULL);

node = *head;
new_node = malloc(sizeof(list_t));

if (!new_node)
return (NULL);
my_memset((void *)new_node, 0, sizeof(list_t));
new_node->num = num;

if (str)
{
new_node->str = _strdup(str);

if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;
return (new_node);
}

/**
 * print_str - prints only the str element of a list_t linked list
 * @l: pointer to first node
 * Return: size of list
 */
size_t print_str(const list_t *l)
{
size_t i = 0;

while (l)
{
_puts(l->str ? l->str : "(nil)");
_puts("\n");
l = l->next;
i++;
}
return (i);
}

/**
 * delete_node - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_node(list_t **head, unsigned int index)
{
list_t *node, *prev_node;
unsigned int i = 0;

if (!head || !*head)
return (0);
if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}
node = *head;

while (node)
{
if (i == index)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
}
return (0);
}
