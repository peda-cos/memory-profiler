#include "tracking.h"
#include "hashtable.h"
#include "backtrace.h"
#include "hooks.h"
#include "memory_profiler.h"
#include <time.h>

t_hashtable	*g_allocations = NULL;
t_stats		g_stats;

void	init_tracking_system(void)
{
	if (!g_allocations)
		g_allocations = ht_create(HASH_TABLE_SIZE);
}

void	update_stats_alloc(size_t size)
{
	g_stats.total_allocations = g_stats.total_allocations + 1;
	g_stats.current_allocations = g_stats.current_allocations + 1;
	g_stats.total_bytes_allocated = g_stats.total_bytes_allocated + size;
	g_stats.current_bytes = g_stats.current_bytes + size;
	if (g_stats.current_allocations > g_stats.peak_allocations)
		g_stats.peak_allocations = g_stats.current_allocations;
	if (g_stats.current_bytes > g_stats.peak_bytes)
		g_stats.peak_bytes = g_stats.current_bytes;
}

t_allocation	*create_allocation(void *ptr, size_t size)
{
	t_allocation	*alloc;
	void			*(*real_malloc)(size_t);

	real_malloc = get_real_malloc();
	alloc = real_malloc(sizeof(t_allocation));
	if (!alloc)
		return (NULL);
	alloc->address = ptr;
	alloc->size = size;
	alloc->timestamp = time(NULL);
	alloc->next = NULL;
	return (alloc);
}

void	capture_stack_trace(t_allocation *alloc)
{
	if (g_config.track_backtrace)
		alloc->backtrace_size = capture_backtrace(alloc->backtrace,
				MAX_BACKTRACE_DEPTH);
}

void	reset_tracking(void)
{
	g_stats.total_allocations = 0;
	g_stats.total_frees = 0;
	g_stats.current_allocations = 0;
	g_stats.peak_allocations = 0;
	g_stats.total_bytes_allocated = 0;
	g_stats.total_bytes_freed = 0;
	g_stats.current_bytes = 0;
	g_stats.peak_bytes = 0;
}
