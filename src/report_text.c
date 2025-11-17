#include "report.h"
#include "tracking.h"
#include <fcntl.h>
#include <unistd.h>

static int	open_report_file(const char *path)
{
	int	fd;

	if (!path || path[0] == '\0')
		return (STDOUT_FILENO);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (STDOUT_FILENO);
	return (fd);
}

void	generate_text_report(const char *path)
{
	int			fd;
	t_stats		*stats;
	t_leak_info	*leaks;

	fd = open_report_file(path);
	write(fd, "=== Memory Profiler Report ===\n\n", 32);
	stats = get_stats();
	if (stats)
		write_stats_text(fd, stats);
	leaks = detect_leaks();
	if (leaks)
	{
		write_leaks_text(fd, leaks);
		free_leak_info(leaks);
	}
	if (fd != STDOUT_FILENO)
		close(fd);
}
