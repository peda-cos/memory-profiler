#ifndef REPORT_H
# define REPORT_H

# include "memory_profiler.h"
# include "leak_detector.h"

void	generate_text_report(const char *path);
void	generate_json_report(const char *path);
void	generate_csv_report(const char *path);
void	write_stats_text(int fd, t_stats *stats);
void	write_leaks_text(int fd, t_leak_info *leaks);

#endif
