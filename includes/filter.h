#ifndef FILTER_H
# define FILTER_H

# include "tracking.h"

typedef struct s_filter
{
	size_t	min_size;
	size_t	max_size;
	char	*source_filter;
}	t_filter;

int		should_include_allocation(t_allocation *alloc, t_filter *filter);
void	init_filter(t_filter *filter);
void	set_filter_min_size(t_filter *filter, size_t min);
void	set_filter_max_size(t_filter *filter, size_t max);

#endif
