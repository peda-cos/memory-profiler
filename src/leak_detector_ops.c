#include "leak_detector.h"
#include "hashtable.h"
#include "hooks.h"
#include <unistd.h>

extern t_hashtable	*g_allocations;

t_leak_info	*create_leak_info(void);
void	allocate_leak_array(t_leak_info *info);

static t_leak_info	*g_current_leak_info = NULL;

static void	count_leak_callback(t_allocation *alloc)
{
	if (!g_current_leak_info || !alloc)
		return ;
	g_current_leak_info->num_leaks = g_current_leak_info->num_leaks + 1;
	g_current_leak_info->total_leaked_bytes += alloc->size;
}

static void	collect_leak_callback(t_allocation *alloc)
{
	static size_t	index = 0;

	if (!g_current_leak_info || !alloc)
		return ;
	if (!g_current_leak_info->leaks)
		return ;
	g_current_leak_info->leaks[index] = alloc;
	index = index + 1;
}

t_leak_info	*detect_leaks(void)
{
	t_leak_info	*info;

	if (!g_allocations)
		return (NULL);
	info = create_leak_info();
	if (!info)
		return (NULL);
	g_current_leak_info = info;
	ht_iterate(g_allocations, count_leak_callback);
	if (info->num_leaks == 0)
	{
		g_current_leak_info = NULL;
		return (info);
	}
	allocate_leak_array(info);
	if (!info->leaks)
	{
		g_current_leak_info = NULL;
		return (info);
	}
	ht_iterate(g_allocations, collect_leak_callback);
	g_current_leak_info = NULL;
	g_current_leak_info = NULL;
	return (info);
}

void	free_leak_info(t_leak_info *info)
{
	void	(*real_free)(void *);

	if (!info)
		return ;
	real_free = get_real_free();
	if (info->leaks)
		real_free(info->leaks);
	real_free(info);
}
