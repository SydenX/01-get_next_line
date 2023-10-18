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

char	*ft_strnjoin(const char *s1, const char *s2, int max)
{
	char	*str;
	int		i;
	int		j;

	if (ft_strlen(s2) < max)
		str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	else
		str = malloc((ft_strlen(s1) + max + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	j = 0;
	i = 0;
	while (s1[i] != 0)
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != 0 && j < max)
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = 0;
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

char	*ft_str(int fd, char *buff, char *str, int start)
{
	static int 	j = 0;
	int			i;

	i = 0;
	printf("%d\n", start);
	// if (ft_readline(fd, buff) == -1)
	// 	return (NULL);
	while (buff[i] != 0 && buff[i] != '\n')
		i++;
	if (str == NULL)
	{
		str = malloc((1) * sizeof(char));
		//printf("AAA");
		str[0] = 0;
		if (str == NULL)
			return (NULL);
	}
	str = ft_strnjoin(str, buff, i);
	//ft_strlcpy(str, buff, i + 1);
	j++;
	//printf("%c", buff[i]);
	if (buff[i] == '\n')
		str[ft_strlen(str)] = 0;
	else if (ft_readline(fd, buff) != -1)
		ft_str(fd, buff, str, start + i);
	return (str);
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
		buff[BUFFER_SIZE] = 0;
	}
	if(ft_readline(fd, buff) == -1)
	{
		free(buff);
		buff == NULL;
		return (NULL);
	}
	str = ft_str(fd, buff, NULL, 0);
	if (str == NULL)
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
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
	while (i < 1){
		printf("%s", get_next_line(fd));
		i++;
	}
	return (argc);
}