#include "utils.h"
#include "hooks.h"
#include <stddef.h>

size_t	safe_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len = len + 1;
	return (len);
}

char	*safe_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;
	void	*(*real_malloc)(size_t);

	if (!s)
		return (NULL);
	len = safe_strlen(s);
	real_malloc = get_real_malloc();
	dup = real_malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i = i + 1;
	}
	dup[len] = '\0';
	return (dup);
}

int	safe_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i = i + 1;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
