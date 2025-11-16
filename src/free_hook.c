#include "hooks.h"
#include "tracking.h"
#include "memory_profiler.h"
#include <stddef.h>

static void	call_real_free(void *ptr)
{
	void	(*real_free)(void *);

	real_free = get_real_free();
	real_free(ptr);
}

void	free(void *ptr)
{
	if (!ptr)
		return ;
	if (is_in_hook())
	{
		call_real_free(ptr);
		return ;
	}
	set_in_hook(1);
	if (g_config.enabled)
		track_free(ptr);
	call_real_free(ptr);
	set_in_hook(0);
}
