#include "report.h"
#include "tracking.h"
#include <unistd.h>

void	write_number(int fd, size_t n)
{
	char	buffer[32];
	int		i;

	i = 0;
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	while (n > 0)
	{
		buffer[i] = (n % 10) + '0';
		n = n / 10;
		i = i + 1;
	}
	while (i > 0)
	{
		i = i - 1;
		write(fd, &buffer[i], 1);
	}
}

void	write_stats_text(int fd, t_stats *stats)
{
	if (!stats)
		return ;
	write(fd, "=== Allocation Statistics ===\n", 30);
	write(fd, "Total allocations: ", 19);
	write_number(fd, stats->total_allocations);
	write(fd, "\nTotal frees: ", 14);
	write_number(fd, stats->total_frees);
	write(fd, "\nCurrent allocations: ", 21);
	write_number(fd, stats->current_allocations);
	write(fd, "\nPeak allocations: ", 18);
	write_number(fd, stats->peak_allocations);
	write(fd, "\n\n", 2);
}

void	write_leaks_text(int fd, t_leak_info *leaks)
{
	if (!leaks)
		return ;
	write(fd, "=== Memory Leaks ===\n", 21);
	write(fd, "Leaked allocations: ", 20);
	write_number(fd, leaks->num_leaks);
	write(fd, "\nLeaked bytes: ", 14);
	write_number(fd, leaks->total_leaked_bytes);
	write(fd, "\n\n", 2);
}
