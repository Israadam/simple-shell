#include "shell.h"

/**
 * get_thehistory_file - gets the history file
 * @parg: parameter structure
 * Return: allocated string containg history file
 */

char *get_thehistory_file(info_t *parg)
{
char *buf, *dir;

dir = _getenv(parg, "HOME=");
if (!dir)
return (NULL);
buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
_strcpy(buf, dir);
_strcat(buf, "/");
_strcat(buf, HIST_FILE);
return (buf);
}


/**
 * build_history_link - adds entry to a history linked list
 * @parg: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @hxlinecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_link(info_t *parg, char *buf, int hxlinecount)
{
list_t *node = NULL;

if (parg->history)
node = parg->history;
add_node_end(&node, buf, hxlinecount);
if (!parg->history)
parg->history = node;
return (0);
}




/**
 * wrt_history - creates a file, or appends to an existing file
 * @parg: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int wrt_history(info_t *parg)
{
ssize_t fd;
char *filename = get_history_file(parg);
list_t *node = NULL;

if (!filename)
return (-1);

fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = parg->history; node; node = node->next)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
}
_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}

/**
 * read_history - reads history from file
 * @parg:the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *parg)
{
int i, last = 0, linecount = 0;
ssize_t fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = get_history_file(parg);
if (!filename)
return (0);

fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.st_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
build_history_list(parg, buf + last, linecount++);
last = i + 1;
}
if (last != i)
build_history_list(parg, buf + last, linecount++);
free(buf);
parg->histcount = linecount;
while (parg->histcount-- >= HIST_MAX)
delete_node_at_index(&(parg->history), 0);
renumber_history(parg);
return (parg->histcount);
}



/**
 * renumber_hist - renumbers the history linked list after changes
 * @parg: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_hist(info_t *parg)
{
list_t *node = parg->history;
int i = 0;
while (node)
{
node->num = i++;
node = node->next;
}
return (parg->histcount = i);
}
