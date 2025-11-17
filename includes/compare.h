#ifndef COMPARE_H
# define COMPARE_H

# include "tracking.h"

typedef struct s_snapshot
{
	t_stats		stats;
	time_t		timestamp;
	size_t		num_allocations;
	t_allocation	**allocations;
}	t_snapshot;

t_snapshot	*create_snapshot(void);
void		free_snapshot(t_snapshot *snapshot);
void		compare_snapshots(t_snapshot *s1, t_snapshot *s2);
void		print_snapshot_diff(t_snapshot *s1, t_snapshot *s2);

#endif
