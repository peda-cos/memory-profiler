#define _GNU_SOURCE
#include "hooks.h"
#include "tracking.h"
#include "memory_profiler.h"
#include <dlfcn.h>
#include <stddef.h>

static __thread int	g_in_hook = 0;

int	is_in_hook(void)
{
	return (g_in_hook);
}

void	set_in_hook(int value)
{
	g_in_hook = value;
}

void	*get_real_malloc(void)
{
	static void	*(*real_malloc)(size_t) = NULL;

	if (!real_malloc)
		real_malloc = dlsym(RTLD_NEXT, "malloc");
	return (real_malloc);
}

void	*get_real_free(void)
{
	static void	(*real_free)(void *) = NULL;

	if (!real_free)
		real_free = dlsym(RTLD_NEXT, "free");
	return (real_free);
}

void	*get_real_calloc(void)
{
	static void	*(*real_calloc)(size_t, size_t) = NULL;

	if (!real_calloc)
		real_calloc = dlsym(RTLD_NEXT, "calloc");
	return (real_calloc);
}

void	*get_real_realloc(void)
{
	static void	*(*real_realloc)(void *, size_t) = NULL;

	if (!real_realloc)
		real_realloc = dlsym(RTLD_NEXT, "realloc");
	return (real_realloc);
}
