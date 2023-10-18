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
	i = 0;
	if (buff[i] == 0)
		ft_readline(fd, buff);
	while (buff[i] != 0 && buff[i] != '\n')
		i++;
	str = ft_substr(buff, 0, i);
	if (str == NULL)
	{
		free(buff);
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
	while (i++ < 80)
		printf("%s", get_next_line(fd));
	return (argc);
}