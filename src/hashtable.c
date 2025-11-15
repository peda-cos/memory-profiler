#include "hashtable.h"
#include "hooks.h"
#include <stddef.h>
#include <stdint.h>

size_t	hash_pointer(void *ptr, size_t table_size)
{
	uintptr_t	addr;
	size_t		hash;

	addr = (uintptr_t)ptr;
	hash = addr % table_size;
	return (hash);
}

t_hashtable	*ht_create(size_t size)
{
	t_hashtable	*ht;
	void		*(*real_malloc)(size_t);
	size_t		i;

	real_malloc = get_real_malloc();
	ht = real_malloc(sizeof(t_hashtable));
	if (!ht)
		return (NULL);
	ht->buckets = real_malloc(sizeof(t_allocation *) * size);
	if (!ht->buckets)
		return (NULL);
	ht->size = size;
	ht->count = 0;
	i = 0;
	while (i < size)
	{
		ht->buckets[i] = NULL;
		i = i + 1;
	}
	return (ht);
}
