#include "memory_profiler.h"
#include "signals.h"
#include "tracking.h"
#include <stdlib.h>

t_config	g_config;

static void	init_config_defaults(void)
{
	int	i;

	g_config.enabled = 1;
	g_config.track_backtrace = 1;
	g_config.detect_leaks = 1;
	g_config.min_alloc_size = 0;
	g_config.format = REPORT_TEXT;
	i = 0;
	while (i < MAX_PATH_LEN)
	{
		g_config.output_path[i] = '\0';
		i = i + 1;
	}
}

void	mp_init(void)
{
	init_config_defaults();
	setup_signal_handlers();
}

void	mp_cleanup(void)
{
	mp_generate_report();
	cleanup_signal_handlers();
}

void	mp_set_output_format(t_report_format format)
{
	g_config.format = format;
}

__attribute__((constructor))
static void	memprof_constructor(void)
{
	mp_init();
}

__attribute__((destructor))
static void	memprof_destructor(void)
{
	mp_cleanup();
}
