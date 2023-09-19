#include "shell.h"

/**
 * history_command - Displays the history list, one command per line, preceded
 *                  with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int history_command(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias_command - Unsets an alias.
 * @info: Parameter struct.
 * @alias: The alias to unset.
 * Return: Always 0 on success, 1 on error
 */
int unset_alias_command(info_t *info, char *alias)
{
	char *p, c;
	int ret;

	p = _strchr(alias, '=');
	if (!p)
		return (1);
	c = *p;
	*p = '\0';
	ret = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, alias, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias_command - Sets an alias.
 * @info: Parameter struct.
 * @alias: The alias to set.
 * Return: Always 0 on success, 1 on error
 */
int set_alias_command(info_t *info, char *alias)
{
	char *p;

	p = _strchr(alias, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias_command(info, alias));

	unset_alias_command(info, alias);
	return (add_node_end(&(info->alias), alias, 0) == NULL);
}

/**
 * print_alias_command - Prints an alias.
 * @alias: The alias to print.
 * Return: Always 0 on success, 1 on error
 */
int print_alias_command(char *alias)
{
	char *p = NULL, *a = NULL;

	p = _strchr(alias, '=');
	if (p)
	{
		for (a = alias; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_command - Mimics the alias builtin (man alias).
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int alias_command(info_t *info)
{
	int i = 0;
	char *p = NULL;

	if (info->argc == 1)
	{
		list_t *node = info->alias;

		while (node)
		{
			print_alias_command(node->str);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias_command(info, info->argv[i]);
		else
			print_alias_command(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
