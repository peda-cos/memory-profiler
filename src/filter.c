#include "filter.h"
#include <stddef.h>

void	init_filter(t_filter *filter)
{
	if (!filter)
		return ;
	filter->min_size = 0;
	filter->max_size = (size_t)-1;
	filter->source_filter = NULL;
}

void	set_filter_min_size(t_filter *filter, size_t min)
{
	if (!filter)
		return ;
	filter->min_size = min;
}

void	set_filter_max_size(t_filter *filter, size_t max)
{
	if (!filter)
		return ;
	filter->max_size = max;
}

static int	check_size_filter(t_allocation *alloc, t_filter *filter)
{
	if (alloc->size < filter->min_size)
		return (0);
	if (alloc->size > filter->max_size)
		return (0);
	return (1);
}

int	should_include_allocation(t_allocation *alloc, t_filter *filter)
{
	if (!alloc || !filter)
		return (1);
	if (!check_size_filter(alloc, filter))
		return (0);
	return (1);
}
