#include "shell.h"

/**
 * split_string - Splits a string into words. Repeat delimiters are ignored.
 * @str: The input string.
 * @delimiters: The delimiter string.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **split_string(char *str, char *delimiters)
{
	int i, j, k, m, num_words = 0;
	char **strings;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	if (!delimiters)
		delimiters = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimiter(str[i], delimiters) &&
				(is_delimiter(str[i + 1], delimiters) || !str[i + 1]))
			num_words++;
	if (num_words == 0)
		return (NULL);
	strings = malloc((1 + num_words) * sizeof(char *));
	if (!strings)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimiter(str[i], delimiters))
			i++;
		k = 0;
		while (!is_delimiter(str[i + k], delimiters) && str[i + k])
			k++;
		strings[j] = malloc((k + 1) * sizeof(char));
		if (!strings[j])
		{
			for (k = 0; k < j; k++)
				free(strings[k]);
			free(strings);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			strings[j][m] = str[i++];

		strings[j][m] = '\0';
	}
	strings[j] = NULL;
	return (strings);
}
/**
 * split_string2 - Splits a string into words.
 * @str: The input string.
 * @delimiter: The delimiter character.
 *
 * Return: A pointer to an array of strings, or NULL on failure.
 */
char **split_string2(char *str, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **strings;

	if (str == NULL || str[0] == '\0')
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != delimiter && str[i + 1] == delimiter) ||
				(str[i] != delimiter && !str[i + 1]) || str[i + 1] == delimiter)
			num_words++;
	if (num_words == 0)
		return (NULL);
	strings = malloc((1 + num_words) * sizeof(char *));
	if (!strings)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == delimiter && str[i] != delimiter)
			i++;
		k = 0;
		while (str[i + k] != delimiter && str[i + k] && str[i + k] != delimiter)
			k++;
		strings[j] = malloc((k + 1) * sizeof(char));
		if (!strings[j])
		{
			for (k = 0; k < j; k++)
				free(strings[k]);
			free(strings);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			strings[j][m] = str[i++];

		strings[j][m] = '\0';
	}
	strings[j] = NULL;
	return (strings);
}
