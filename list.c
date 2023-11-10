#include "shell.h"

/**
 * add_nodelist - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @nhx: node index used by history
 *
 * Return: size of list
 */
list_t *add_nodelist(list_t **head, const char *str, int nhx)
{
list_t *new_head;
if (!head)
return (NULL);
new_head = malloc(sizeof(list_t));
if (!new_head)
return (NULL);
_memset((void *)new_head, 0, sizeof(list_t));
new_head->nhx = nhx;
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
 * add_end_node - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @nhx: node index used by history
 *
 * Return: size of list
 */
list_t *add_end_node(list_t **head, const char *str, int nhx)
{
list_t *new_node, *node;
if (!head)
return (NULL);
node = *head;
new_node = malloc(sizeof(list_t));
if (!new_node)
return (NULL);
_memset((void *)new_node, 0, sizeof(list_t));
new_node->nhx = nhx;
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
 * free_node_list - frees all nodes of a list
 * @head_pointer: address of pointer to head nod
 * Return: void
 */
void free_node_list(list_t **head_pointer)
{
list_t *node, *next_node, *head;
if (!head_pointer || !*head_pointer)
return;
head = *head_pointer;
node = head;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}
*head_pointer = NULL;
}
/**
 * print_lst_str - prints only the str element of a list_t linked list
 * @m: pointer to first node
 * Return: size of list
 */
size_t print_lst_str(const list_t *m)
{
size_t i = 0;
while (m)
{
_puts(m->str ? m->str : "(nil)");
_puts("\n");
m = m->next;
i++;
return (i);
}

/**
 * delete_node_at_given_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_given_index(list_t **head, unsigned int index)
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
}
