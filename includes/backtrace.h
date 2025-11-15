#ifndef BACKTRACE_H
# define BACKTRACE_H

# include "memory_profiler.h"

int		capture_backtrace(void **buffer, int max_frames);
char	**get_backtrace_symbols(void **buffer, int size);
void	free_backtrace_symbols(char **symbols);

#endif
