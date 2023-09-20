#include "shell.h"

/**
 * copyEnvironment - returns a copy of the environment as a string array.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: A copy of the environment as a string array.
 */
char **copyEnvironment(info_t *info)
{
	if (!info->environ || info->envChanged)
	{
		info->environ = listToStrings(info->env);
		info->envChanged = 0;
	}
	return (info->environ);
}

/**
 * unsetEnvironmentVariable - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * @var: The environment variable to remove.
 * Return: 1 on successful deletion, 0 otherwise.
 */
int unsetEnvironmentVariable(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			info->envChanged = deleteNodeAtIndex(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->envChanged);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable
 *                         or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The environment variable name.
 * @value: The environment variable value.
 * Return: 0 on success, 1 on failure.
 */
int setEnvironmentVariable(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (1);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		p = startsWith(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->envChanged = 1;
			return (0);
		}
		node = node->next;
	}
	addNodeEnd(&(info->env), buf, 0);
	free(buf);
	info->envChanged = 1;
	return (0);
}
