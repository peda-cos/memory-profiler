#include "leak_detector.h"
#include "hashtable.h"
#include "hooks.h"
#include <stddef.h>

extern t_hashtable	*g_allocations;

t_leak_info	*create_leak_info(void)
{
	t_leak_info	*info;
	void		*(*real_malloc)(size_t);

	real_malloc = get_real_malloc();
	info = real_malloc(sizeof(t_leak_info));
	if (!info)
		return (NULL);
	info->total_leaked_bytes = 0;
	info->num_leaks = 0;
	info->leaks = NULL;
	info->next = NULL;
	return (info);
}

void	count_leak(t_allocation *alloc, void *data)
{
	t_leak_info	*info;

	info = (t_leak_info *)data;
	if (!info || !alloc)
		return ;
	info->num_leaks = info->num_leaks + 1;
	info->total_leaked_bytes = info->total_leaked_bytes + alloc->size;
}

void	allocate_leak_array(t_leak_info *info)
{
	void	*(*real_malloc)(size_t);
	size_t	size;

	real_malloc = get_real_malloc();
	size = sizeof(t_allocation *) * info->num_leaks;
	info->leaks = real_malloc(size);
}

void	collect_leak(t_allocation *alloc, void *data)
{
	t_leak_info		*info;
	static size_t	index = 0;

	info = (t_leak_info *)data;
	if (!info || !alloc || !info->leaks)
		return ;
	info->leaks[index] = alloc;
	index = index + 1;
}

t_leak_info	*create_leak_info(void);
void	count_leak(t_allocation *alloc, void *data);
void	allocate_leak_array(t_leak_info *info);
void	collect_leak(t_allocation *alloc, void *data);
