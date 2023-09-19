#include "shell.h"

/**
 * _memory_set - Fills memory with a constant byte.
 * @ptr: Pointer to the memory area.
 * @byte: The byte to fill the memory with.
 * @size: The number of bytes to be filled.
 *
 * Return: A pointer to the memory area @ptr.
 */
char *_memory_set(char *ptr, char byte, unsigned int size)
{
	unsigned int i;

	for (i = 0; i < size; i++)
		ptr[i] = byte;
	return (ptr);
}

/**
 * free_string_array - Frees an array of strings.
 * @str_array: Array of strings.
 */
void free_string_array(char **str_array)
{
	char **tmp = str_array;

	if (!str_array)
		return;

	while (*str_array)
		free(*str_array++);

	free(tmp);
}

/**
 * custom_realloc - Reallocates a block of memory.
 * @ptr: Pointer to the previous malloc'ed block.
 * @old_size: Byte size of the previous block.
 * @new_size: Byte size of the new block.
 *
 * Return: Pointer to the reallocated block.
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;

	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];

	free(ptr);
	return (new_ptr);
}
