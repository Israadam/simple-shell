#include "shell.h"
/**
 * duplicate_chars - duplicates characters
 * @str: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *duplicate_chars(char *str, int start, int stop)
{
	static char buffer[1024];
	int i = 0;
	int h = 0;

	for (h = 0, i = start; i < stop; i++)
		if (str[i] != ':')
			buffer[h++] = str[i];
	buffer[h] = 0;
	return (buffer);
}


/**
 * path_str - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *path_str(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && start_with(cmd, "./"))
	{
		if (_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = duplicate_chars(pathstr, pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			pos = i;
		}
		i++;
	}
	return (NULL);
}

/**
 * _cmd - determines if a file is an executable command
 * @data: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int _cmd(info_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
