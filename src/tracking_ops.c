#include "tracking.h"
#include "hashtable.h"
#include "hooks.h"
#include "memory_profiler.h"

extern t_hashtable	*g_allocations;
extern t_stats		g_stats;

void	init_tracking_system(void);
void	update_stats_alloc(size_t size);
t_allocation	*create_allocation(void *ptr, size_t size);
void	capture_stack_trace(t_allocation *alloc);

void	track_allocation(void *ptr, size_t size)
{
	t_allocation	*alloc;

	if (!ptr)
		return ;
	init_tracking_system();
	alloc = create_allocation(ptr, size);
	if (!alloc)
		return ;
	capture_stack_trace(alloc);
	ht_insert(g_allocations, alloc);
	update_stats_alloc(size);
}

static void	update_stats_free(size_t size)
{
	g_stats.total_frees = g_stats.total_frees + 1;
	g_stats.current_allocations = g_stats.current_allocations - 1;
	g_stats.total_bytes_freed = g_stats.total_bytes_freed + size;
	g_stats.current_bytes = g_stats.current_bytes - size;
}

void	track_free(void *ptr)
{
	t_allocation	*alloc;
	void			(*real_free)(void *);

	if (!ptr || !g_allocations)
		return ;
	alloc = ht_find(g_allocations, ptr);
	if (alloc)
	{
		update_stats_free(alloc->size);
		ht_remove(g_allocations, ptr);
		real_free = get_real_free();
		real_free(alloc);
	}
}

t_allocation	*get_allocation(void *ptr)
{
	if (!g_allocations)
		return (NULL);
	return (ht_find(g_allocations, ptr));
}

t_stats	*get_stats(void)
{
	return (&g_stats);
}
