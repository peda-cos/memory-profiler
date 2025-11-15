#include "tracking.h"
#include "hooks.h"
#include <stddef.h>

t_allocation	*list_create_node(void *addr, size_t size)
{
	t_allocation	*node;
	void			*(*real_malloc)(size_t);

	real_malloc = get_real_malloc();
	node = real_malloc(sizeof(t_allocation));
	if (!node)
		return (NULL);
	node->address = addr;
	node->size = size;
	node->next = NULL;
	return (node);
}

void	list_append(t_allocation **head, t_allocation *new_node)
{
	t_allocation	*current;

	if (!head || !new_node)
		return ;
	if (!*head)
	{
		*head = new_node;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

void	list_free(t_allocation *head)
{
	t_allocation	*current;
	t_allocation	*next;
	void			(*real_free)(void *);

	real_free = get_real_free();
	current = head;
	while (current)
	{
		next = current->next;
		real_free(current);
		current = next;
	}
}
