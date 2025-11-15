#ifndef MEMORY_PROFILER_H
# define MEMORY_PROFILER_H

# include <stddef.h>
# include <stdint.h>
# include <time.h>

# define MAX_BACKTRACE_DEPTH 64
# define HASH_TABLE_SIZE 4096
# define MAX_PATH_LEN 256
# define MAX_SYMBOL_LEN 512

typedef enum e_report_format
{
	REPORT_TEXT,
	REPORT_JSON,
	REPORT_CSV
}	t_report_format;

typedef enum e_filter_type
{
	FILTER_NONE,
	FILTER_SIZE_MIN,
	FILTER_SIZE_MAX,
	FILTER_SOURCE
}	t_filter_type;

typedef struct s_config
{
	int				enabled;
	int				track_backtrace;
	int				detect_leaks;
	size_t			min_alloc_size;
	t_report_format	format;
	char			output_path[MAX_PATH_LEN];
}	t_config;

extern t_config	g_config;

void	mp_init(void);
void	mp_cleanup(void);
void	mp_generate_report(void);
void	mp_set_output_format(t_report_format format);

#endif
