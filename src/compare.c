#include "compare.h"
#include "tracking.h"
#include "hooks.h"
#include <time.h>

t_snapshot	*create_snapshot(void)
{
	t_snapshot	*snapshot;
	t_stats		*stats;
	void		*(*real_malloc)(size_t);

	real_malloc = get_real_malloc();
	snapshot = real_malloc(sizeof(t_snapshot));
	if (!snapshot)
		return (NULL);
	stats = get_stats();
	if (stats)
		snapshot->stats = *stats;
	snapshot->timestamp = time(NULL);
	snapshot->num_allocations = 0;
	snapshot->allocations = NULL;
	return (snapshot);
}

void	free_snapshot(t_snapshot *snapshot)
{
	void	(*real_free)(void *);

	if (!snapshot)
		return ;
	real_free = get_real_free();
	if (snapshot->allocations)
		real_free(snapshot->allocations);
	real_free(snapshot);
}
