


#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}



char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ss;
	size_t	lss;
	size_t	ls;

	lss = 0;
	if (!s)
		return (0);
	ls = ft_strlen(s);
	if (start > ls)
	{
		lss = 0;
		start = ls;
	}
	else if (ls - start < len)
		lss = ls - start;
	else if (ls - start >= len)
		lss = len;
	ss = malloc(lss * sizeof(char) + 1);
	if (ss == 0)
		return (0);
	ft_strlcpy(ss, &s[start], lss + 1);
	return (ss);
}


static int	set_check(char s1, char const *set)
{
	size_t	j;

	j = 0;
	while (set[j] != '\0')
	{
		if (s1 == set[j])
		{
			return (1);
		}
		j++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	skip;
	size_t	ls;

	skip = 0;
	if (!s1 || !set)
		return (0);
	ls = ft_strlen(s1);
	while (s1[skip] && set_check(s1[skip], set) == 1)
		skip++;
	while (ls > skip && set_check(s1[ls - 1], set) == 1)
		ls--;
	return (ft_substr(s1, skip, ls - skip));
}
