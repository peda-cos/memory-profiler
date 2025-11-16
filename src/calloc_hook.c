#include "hooks.h"
#include "tracking.h"
#include "memory_profiler.h"
#include <stddef.h>

static void	*call_real_calloc(size_t nmemb, size_t size)
{
	void	*(*real_calloc)(size_t, size_t);
	void	*ptr;

	real_calloc = get_real_calloc();
	ptr = real_calloc(nmemb, size);
	return (ptr);
}

void	*calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	if (is_in_hook())
		return (call_real_calloc(nmemb, size));
	set_in_hook(1);
	ptr = call_real_calloc(nmemb, size);
	total_size = nmemb * size;
	if (ptr && g_config.enabled)
		track_allocation(ptr, total_size);
	set_in_hook(0);
	return (ptr);
}
