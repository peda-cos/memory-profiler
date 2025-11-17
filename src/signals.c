#include "signals.h"
#include "memory_profiler.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	signal_handler(int signum)
{
	if (signum == SIGINT || signum == SIGTERM)
	{
		write(STDERR_FILENO, "\nGenerating memory report...\n", 29);
		mp_cleanup();
		exit(0);
	}
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
}

void	cleanup_signal_handlers(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
}
