#include "hashtable.h"
#include "hooks.h"

size_t	hash_pointer(void *ptr, size_t table_size);
void	remove_from_bucket(t_hashtable *ht, size_t idx, void *ptr);

void	ht_remove(t_hashtable *ht, void *ptr)
{
	size_t	index;

	if (!ht || !ptr)
		return ;
	index = hash_pointer(ptr, ht->size);
	remove_from_bucket(ht, index, ptr);
}

void	ht_iterate(t_hashtable *ht, void (*fn)(t_allocation *))
{
	size_t			i;
	t_allocation	*current;
	t_allocation	*next;

	if (!ht || !fn)
		return ;
	i = 0;
	while (i < ht->size)
	{
		current = ht->buckets[i];
		while (current)
		{
			next = current->next;
			fn(current);
			current = next;
		}
		i = i + 1;
	}
}

void	ht_destroy(t_hashtable *ht)
{
	void	(*real_free)(void *);

	if (!ht)
		return ;
	real_free = get_real_free();
	if (ht->buckets)
		real_free(ht->buckets);
	real_free(ht);
}
