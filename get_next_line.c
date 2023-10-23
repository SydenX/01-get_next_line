/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:39:41 by jtollena          #+#    #+#             */
/*   Updated: 2023/10/23 15:21:15 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

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

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*copy;

	copy = s;
	while (n > 0)
	{
		*copy = 0;
		copy++;
		n--;
	}
}

int	ft_strchr(const char *s, int c)
{
	char	*copy;
	int		i;

	i = 0;
	copy = (char *) s;
	if (copy == NULL)
		return (-1);
	while (copy[i] != 0)
	{
		if (copy[i] == (unsigned char)c)
			return (i);
		i++;
	}
	if (copy[i] == (char)c)
		return (i);
	return (-1);
}

char	*ft_subbuff(char *tmp, char *buff, int maxsub)
{
	char	*str;
	char	*substr;
	char	*buffcpy;

	buffcpy = ft_strdup(buff);
	if (buffcpy == NULL)
		return (NULL);
	ft_bzero(buff, BUFFER_SIZE + 1);
	str = ft_strdup(tmp);
	if (str == NULL)
	{
		free(buffcpy);
		return (NULL);
	}
	free(tmp);
	printf("%d-", maxsub);
	substr = ft_substr(buffcpy, 0, maxsub);
	ft_strlcpy(buff, buffcpy, BUFFER_SIZE - maxsub + 1);
	free(buffcpy);
	if (substr == NULL)
	{
		free(str);
		free(tmp);
		return (NULL);
	}
	tmp = ft_strjoin(str, substr);
	free(substr);
	free(str);
	if (tmp == NULL)
		return (NULL);
	return (tmp);
}

char	*ft_str(int fd, char *buff)
{
	char	*tmp;
	int		red;

	tmp = ft_strdup("");
	if (tmp == NULL)
		return (NULL);
	while (ft_strchr(buff, '\n') == -1)
	{
		tmp = ft_subbuff(tmp, buff, ft_strlen(buff));
		red = read(fd, buff, BUFFER_SIZE);
		if(red <= 0)
		{
			printf("-%s-", buff);
			buff = NULL;
			return (tmp);
		}
	}
	tmp = ft_subbuff(tmp, buff, ft_strchr(buff, '\n') + 1);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*buff = 0;
	char		*str;
	int			i;

	if (!ft_file_check(fd, buff))
		return (NULL);
	if (buff == 0)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buff == NULL)
			return (NULL);
		buff[BUFFER_SIZE] = 0;
		if(read(fd, buff, BUFFER_SIZE) <= 0)
		{
			free(buff);
			buff = NULL;
			return (NULL);
		}
		str = ft_str(fd, buff);
	}
	else if (buff != NULL)
		str = ft_str(fd, buff);
	if (buff == NULL)
		return (NULL);
	if (str == NULL || str[0] == 0)
	{
		if(str[0] == 0)
			free(str);
		if (buff != NULL)
			free(buff);
		buff = NULL;
		return (NULL);
	}
	if (ft_strchr(buff, '\n') == -1)
	{
		free(buff);
		buff = NULL;
		return (str);
	}
	else
	{
		i = ft_strchr(buff, '\n') + 1;
		ft_strlcpy(buff, &buff[i], ft_strlen(&buff[i]) + 1);
	}
	return (str);
}

#include <stdio.h>
int	main(int argc, char *argv[]){
	int	fd = open(argv[1], O_RDONLY, 0);
	int i = 0;
	while (i < 12){
		printf("%s", get_next_line(fd));
		i++;
	}
	return (argc);
}