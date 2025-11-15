#ifndef TRACKING_H
# define TRACKING_H

# include "memory_profiler.h"
# include <stddef.h>
# include <time.h>

typedef struct s_allocation
{
	void				*address;
	size_t				size;
	time_t				timestamp;
	void				*backtrace[MAX_BACKTRACE_DEPTH];
	int					backtrace_size;
	struct s_allocation	*next;
}	t_allocation;

typedef struct s_stats
{
	size_t	total_allocations;
	size_t	total_frees;
	size_t	current_allocations;
	size_t	peak_allocations;
	size_t	total_bytes_allocated;
	size_t	total_bytes_freed;
	size_t	current_bytes;
	size_t	peak_bytes;
}	t_stats;

void			track_allocation(void *ptr, size_t size);
void			track_free(void *ptr);
t_allocation	*get_allocation(void *ptr);
t_stats			*get_stats(void);
void			reset_tracking(void);

#endif
