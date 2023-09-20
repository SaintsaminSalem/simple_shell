#include "shell.h"

/**
 * addNode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of the node
 * @num: node index used by history
 *
 * Return: pointer to the newly added node
 */
list_t *addNode(list_t **head, const char *str, int num)
{
	list_t *newNode;

	if (!head)
		return (NULL);

	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);

	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;

	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}

	newNode->next = *head;
	*head = newNode;
	return (newNode);
}

/**
 * addNodeEnd - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of the node
 * @num: node index used by history
 *
 * Return: pointer to the newly added node
 */
list_t *addNodeEnd(list_t **head, const char *str, int num)
{
	list_t *newNode, *node;

	if (!head)
		return (NULL);

	node = *head;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);

	_memset((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;

	if (str)
	{
		newNode->str = _strdup(str);
		if (!newNode->str)
		{
			free(newNode);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*head = newNode;

	return (newNode);
}

/**
 * printListStr - prints only the str element of a list_t linked list
 * @h: pointer to the first node
 *
 * Return: size of list
 */
size_t printListStr(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * deleteNodeAtIndex - deletes a node at a given index
 * @head: address of pointer to first node
 * @index: index of the node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int deleteNodeAtIndex(list_t **head, unsigned int index)
{
	list_t *node, *prevNode;
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
			prevNode->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prevNode = node;
		node = node->next;
	}
	return (0);
}

/**
 * freeList - frees all nodes of a list
 * @headPtr: address of pointer to head node
 *
 * Return: void
 */
void freeList(list_t **headPtr)
{
	list_t *node, *nextNode, *head;

	if (!headPtr || !*headPtr)
		return;

	head = *headPtr;
	node = head;

	while (node)
	{
		nextNode = node->next;
		free(node->str);
		free(node);
		node = nextNode;
	}

	*headPtr = NULL;
}
