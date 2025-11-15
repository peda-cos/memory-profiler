#include "backtrace.h"
#include <execinfo.h>
#include <stdlib.h>

int	capture_backtrace(void **buffer, int max_frames)
{
	int	size;

	if (!buffer || max_frames <= 0)
		return (0);
	size = backtrace(buffer, max_frames);
	return (size);
}

char	**get_backtrace_symbols(void **buffer, int size)
{
	char	**symbols;

	if (!buffer || size <= 0)
		return (NULL);
	symbols = backtrace_symbols(buffer, size);
	return (symbols);
}

void	free_backtrace_symbols(char **symbols)
{
	if (symbols)
		free(symbols);
}
