#include "shell.h"

/**
 * printEnvironment - prints the current environment.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int printEnvironment(info_t *info)
{
	printListString(info->env);
	return (0);
}

/**
 * getEnvironment - gets the value of an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * @name: Name of the environment variable.
 *
 * Return: The value of the environment variable.
 */
char *getEnvironment(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = startsWith(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * setEnvironment - Initialize a new environment variable
 * or modify an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
 */
int setEnvironment(info_t *info)
{
	if (info->argc != 3)

	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setEnvironment(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetEnvironment - Remove an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
 */
int unsetEnvironment(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetEnvironment(info, info->argv[i]);

	return (0);
}

/**
 * populateEnvironmentList - Populates the environment linked list.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0.
 */
int populateEnvironmentList(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}
