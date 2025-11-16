#include "hooks.h"
#include "tracking.h"
#include "memory_profiler.h"
#include <stddef.h>

static void	*call_real_malloc(size_t size)
{
	void	*(*real_malloc)(size_t);
	void	*ptr;

	real_malloc = get_real_malloc();
	ptr = real_malloc(size);
	return (ptr);
}

void	*malloc(size_t size)
{
	void	*ptr;

	if (is_in_hook())
		return (call_real_malloc(size));
	set_in_hook(1);
	ptr = call_real_malloc(size);
	if (ptr && g_config.enabled)
		track_allocation(ptr, size);
	set_in_hook(0);
	return (ptr);
}
