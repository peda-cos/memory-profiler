#include "leak_detector.h"
#include <unistd.h>

static void	write_leak_header(void)
{
	write(STDOUT_FILENO, "\n=== Memory Leak Summary ===\n", 29);
}

static void	write_leak_count(size_t num_leaks)
{
	char	buffer[32];
	int		i;
	size_t	n;

	write(STDOUT_FILENO, "Total leaks: ", 13);
	n = num_leaks;
	i = 0;
	if (n == 0)
	{
		write(STDOUT_FILENO, "0\n", 2);
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
		write(STDOUT_FILENO, &buffer[i], 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

static void	write_bytes_leaked(size_t bytes)
{
	char	buffer[32];
	int		i;
	size_t	n;

	write(STDOUT_FILENO, "Total bytes leaked: ", 20);
	n = bytes;
	i = 0;
	while (n > 0)
	{
		buffer[i] = (n % 10) + '0';
		n = n / 10;
		i = i + 1;
	}
	while (i > 0)
	{
		i = i - 1;
		write(STDOUT_FILENO, &buffer[i], 1);
	}
	write(STDOUT_FILENO, " bytes\n", 7);
}

void	print_leak_summary(t_leak_info *info)
{
	if (!info)
		return ;
	write_leak_header();
	if (info->num_leaks == 0)
	{
		write(STDOUT_FILENO, "No memory leaks detected!\n", 26);
		return ;
	}
	write_leak_count(info->num_leaks);
	write_bytes_leaked(info->total_leaked_bytes);
}
