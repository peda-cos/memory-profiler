#ifndef LEAK_DETECTOR_H
# define LEAK_DETECTOR_H

# include "tracking.h"

typedef struct s_leak_info
{
	size_t				total_leaked_bytes;
	size_t				num_leaks;
	t_allocation		**leaks;
	struct s_leak_info	*next;
}	t_leak_info;

t_leak_info	*detect_leaks(void);
void		free_leak_info(t_leak_info *info);
void		print_leak_summary(t_leak_info *info);

#endif
