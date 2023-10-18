/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:39:41 by jtollena          #+#    #+#             */
/*   Updated: 2023/10/17 10:52:29 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	ln;

	ln = 0;
	while (s[ln] != 0)
		ln++;
	return (ln);
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

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

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	i = 0;
	if (dst == NULL || src == NULL)
		return (0);
	while (i < ((int)dstsize - 1) && src[i] != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize != 0)
		dst[i] = 0;
	return (ft_strlen(src));
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

int	ft_file_check(int fd, char *buff)
{
	if (fd == -1)
	{
		if (buff != 0)
			free(buff);
		buff = NULL;
		return (0);
	}
	return (1);
}

int	ft_readline(int fd, char *buff)
{
	int	readable;
	int	i;

	readable = read(fd, buff, BUFFER_SIZE);
	if (readable < 1)
		return (-1);
	return (readable);
}

void	ft_str(int fd, char *buff, char *str, int start)
{
	int	i;

	i = 0;
	if (buff[i] == 0)
		ft_readline(fd, buff);
	while (buff[i] != 0 && buff[i] != '\n')
		i++;
	str = malloc((i + start + 1) * sizeof(char));
	if (str == NULL)
	{
		free(buff);
		return (NULL);
	}
	ft_strlcpy(str, buff, (int)i + start + 1);
	if (buff[i] == '\n')
		str[ft_strlen(str)] = '\n';
	else if (buff[i] == 0)
		ft_str(str)
	if (buff[i + 1] != 0 && buff[i + 1] != '\n')
	{
		free(str);
		ft_str(fd, buff, str, start + i + 1);
	}
}

char	*get_next_line(int fd)
{
	static char	*buff = 0;
	char		readable = 0;
	int			i;
	char		*str;

	if (!ft_file_check(fd, buff))
		return (NULL);
	if(buff == 0)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buff == NULL)
			return (NULL);
	}
	if (ft_str(fd, buff, 0))
	buff += i + 1;
	return (str);
}

// char	*get_next_lineold(int fd)
// {
// 	static char	*buff = 0;
// 	char		*str;
// 	static int	readable = 0;
// 	static int	i = 0;
// 	int			j;

// 	if (fd == -1)
// 	{
// 		if (buff != NULL)
// 		{	
// 			free(buff);
// 			buff = NULL;
// 		}
// 		return (NULL);
// 	}
// 	if (readable == 0)
// 	{
// 		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 		if (buff == NULL)
// 			return (NULL);
// 		buff[BUFFER_SIZE] = 0;
// 		readable = read(fd, buff, BUFFER_SIZE);
// 		if (readable < 1){
// 			free(buff);
// 			buff = NULL;
// 			return (NULL);
// 		}
// 	}
// 	if (buff == NULL)
// 		return (NULL);
// 	if (i >= BUFFER_SIZE)
// 	{
// 		readable = read(fd, buff, BUFFER_SIZE);
// 		if (readable < 1)
// 		{
// 			free(buff);
// 			buff = NULL;
// 			return (NULL);
// 		}
// 	}
// 	j = 0;
// 	while (buff[i + j] != 0 && buff[i + j] != '\n')
// 		j++;
// 	str = malloc((j + 1) * sizeof(char));
// 	if (str == NULL)
// 	{
// 		free(buff);
// 		buff = NULL;
// 		return (NULL);
// 	}
// 	j = 0;
// 	while (buff[i] != 0 && buff[i] != '\n')
// 	{
// 		str[j] = buff[i];
// 		i++;
// 		j++;
// 	}
// 	if (buff[i] == '\n')
// 		str[j] = '\n';
// 	else
// 		str[j] = 0;
// 	i++;
// 	return (str);
// }

#include <stdio.h>
int	main(int argc, char *argv[]){
	int	fd = open(argv[1], O_RDONLY, 0);
	int i = 0;
	while (i++ < 30)
		printf("%s", get_next_line(fd));
	return (argc);
}