#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "tracking.h"
# include <stddef.h>

typedef struct s_hashtable
{
	t_allocation	**buckets;
	size_t			size;
	size_t			count;
}	t_hashtable;

t_hashtable		*ht_create(size_t size);
void			ht_destroy(t_hashtable *ht);
void			ht_insert(t_hashtable *ht, t_allocation *alloc);
t_allocation	*ht_find(t_hashtable *ht, void *ptr);
void			ht_remove(t_hashtable *ht, void *ptr);
void			ht_iterate(t_hashtable *ht, void (*fn)(t_allocation *));

#endif
