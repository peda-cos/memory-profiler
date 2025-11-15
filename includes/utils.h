#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

void	*safe_memset(void *s, int c, size_t n);
void	*safe_memcpy(void *dest, const void *src, size_t n);
size_t	safe_strlen(const char *s);
char	*safe_strdup(const char *s);
int		safe_strcmp(const char *s1, const char *s2);

#endif
