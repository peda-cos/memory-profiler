#ifndef HOOKS_H
# define HOOKS_H

# include <stddef.h>

void	*malloc(size_t size);
void	free(void *ptr);
void	*calloc(size_t nmemb, size_t size);
void	*realloc(void *ptr, size_t size);

void	*get_real_malloc(void);
void	*get_real_free(void);
void	*get_real_calloc(void);
void	*get_real_realloc(void);

int		is_in_hook(void);
void	set_in_hook(int value);

#endif
