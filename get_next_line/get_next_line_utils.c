/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:19:00 by jtollena          #+#    #+#             */
/*   Updated: 2023/11/16 10:47:54 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dst[0] == 0 && src[0] == 0)
		return (0);
	while (i < dstsize && 
		((src[i] >= 32 && src[i] <= 126)
			|| src[i] == '\n'
			|| (src[i] >= 9 && src[i] <= 13)))
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = 0;
	return (ft_strlen(src));
}

char	*ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if (c == 0)
		return (&s[ft_strlen(s)]);
	return (0);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

	if (!s)
		return (NULL);
	copy = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s[i] != 0)
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = 0;
	return (copy);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(&s[start]) < len)
		len = ft_strlen(&s[start]);
	str = malloc(((int)len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s[start], (int)len + 1);
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (free(s1), free(s2), NULL);
	j = 0;
	i = 0;
	while (*s1 != 0)
		str[i++] = *s1++;
	s1 -= i;
	while (*s2 != 0)
		str[i + j++] = *s2++;
	s2 -= j;
	str[ft_strlen(s1) + ft_strlen(s2)] = 0;
	free(s1);
	return (str);
}
