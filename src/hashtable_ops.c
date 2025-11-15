#include "hashtable.h"
#include "hooks.h"

size_t	hash_pointer(void *ptr, size_t table_size);

void	ht_insert(t_hashtable *ht, t_allocation *alloc)
{
	size_t	index;

	if (!ht || !alloc)
		return ;
	index = hash_pointer(alloc->address, ht->size);
	alloc->next = ht->buckets[index];
	ht->buckets[index] = alloc;
	ht->count = ht->count + 1;
}

t_allocation	*ht_find(t_hashtable *ht, void *ptr)
{
	size_t			index;
	t_allocation	*current;

	if (!ht || !ptr)
		return (NULL);
	index = hash_pointer(ptr, ht->size);
	current = ht->buckets[index];
	while (current)
	{
		if (current->address == ptr)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	remove_from_bucket(t_hashtable *ht, size_t idx, void *ptr)
{
	t_allocation	*prev;
	t_allocation	*curr;

	prev = NULL;
	curr = ht->buckets[idx];
	while (curr)
	{
		if (curr->address == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				ht->buckets[idx] = curr->next;
			ht->count = ht->count - 1;
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
