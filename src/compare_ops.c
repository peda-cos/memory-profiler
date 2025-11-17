#include "compare.h"
#include "utils.h"
#include <unistd.h>

void	write_number(int fd, size_t n);

static void	write_diff_line(const char *label, size_t v1, size_t v2)
{
	write(STDOUT_FILENO, label, safe_strlen(label));
	write(STDOUT_FILENO, ": ", 2);
	write_number(STDOUT_FILENO, v1);
	write(STDOUT_FILENO, " -> ", 4);
	write_number(STDOUT_FILENO, v2);
	write(STDOUT_FILENO, " (", 2);
	if (v2 > v1)
		write(STDOUT_FILENO, "+", 1);
	write_number(STDOUT_FILENO, v2 - v1);
	write(STDOUT_FILENO, ")\n", 2);
}

void	compare_snapshots(t_snapshot *s1, t_snapshot *s2)
{
	if (!s1 || !s2)
		return ;
	write(STDOUT_FILENO, "\n=== Snapshot Comparison ===\n", 28);
	write_diff_line("Current allocations", s1->stats.current_allocations,
		s2->stats.current_allocations);
	write_diff_line("Current bytes", s1->stats.current_bytes,
		s2->stats.current_bytes);
}

void	print_snapshot_diff(t_snapshot *s1, t_snapshot *s2)
{
	compare_snapshots(s1, s2);
}
