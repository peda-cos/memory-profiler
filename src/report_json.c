#include "report.h"
#include "tracking.h"
#include "utils.h"
#include <fcntl.h>
#include <unistd.h>

void	write_number(int fd, size_t n);

static void	write_json_stats(int fd, t_stats *stats)
{
	if (!stats)
		return ;
	write(fd, "  \"statistics\": {\n", 18);
	write(fd, "    \"total_allocations\": ", 25);
	write_number(fd, stats->total_allocations);
	write(fd, ",\n    \"total_frees\": ", 22);
	write_number(fd, stats->total_frees);
	write(fd, ",\n    \"current_allocations\": ", 30);
	write_number(fd, stats->current_allocations);
	write(fd, ",\n    \"peak_allocations\": ", 27);
	write_number(fd, stats->peak_allocations);
	write(fd, "\n  }", 4);
}

void	generate_json_report(const char *path)
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
	write(fd, "{\n", 2);
	stats = get_stats();
	write_json_stats(fd, stats);
	write(fd, ",\n  \"leaks\": {\n", 16);
	leaks = detect_leaks();
	write(fd, "    \"count\": ", 13);
	write_number(fd, leaks ? leaks->num_leaks : 0);
	write(fd, "\n  }\n}\n", 7);
	if (leaks)
		free_leak_info(leaks);
	if (fd != STDOUT_FILENO)
		close(fd);
}
