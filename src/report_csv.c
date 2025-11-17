#include "report.h"
#include "tracking.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

void	write_number(int fd, size_t n);

static void	write_csv_header(int fd)
{
	write(fd, "metric,value\n", 13);
}

static void	write_csv_row(int fd, const char *name, size_t value)
{
	write(fd, name, safe_strlen(name));
	write(fd, ",", 1);
	write_number(fd, value);
	write(fd, "\n", 1);
}

void	generate_csv_report(const char *path)
{
	int			fd;
	t_stats		*stats;
	t_leak_info	*leaks;

	if (!path || path[0] == '\0')
		fd = STDOUT_FILENO;
	else
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return ;
	write_csv_header(fd);
	stats = get_stats();
	if (stats)
	{
		write_csv_row(fd, "total_allocations", stats->total_allocations);
		write_csv_row(fd, "total_frees", stats->total_frees);
		write_csv_row(fd, "current_allocations", stats->current_allocations);
	}
	leaks = detect_leaks();
	if (leaks)
	{
		write_csv_row(fd, "leaked_allocations", leaks->num_leaks);
		free_leak_info(leaks);
	}
	if (fd != STDOUT_FILENO)
		close(fd);
}
