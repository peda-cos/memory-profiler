#include "hooks.h"
#include "tracking.h"
#include "memory_profiler.h"
#include <stddef.h>

static void	*call_real_realloc(void *ptr, size_t size)
{
	void	*(*real_realloc)(void *, size_t);
	void	*new_ptr;

	real_realloc = get_real_realloc();
	new_ptr = real_realloc(ptr, size);
	return (new_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	if (is_in_hook())
		return (call_real_realloc(ptr, size));
	set_in_hook(1);
	if (ptr && g_config.enabled)
		track_free(ptr);
	new_ptr = call_real_realloc(ptr, size);
	if (new_ptr && g_config.enabled)
		track_allocation(new_ptr, size);
	set_in_hook(0);
	return (new_ptr);
}
