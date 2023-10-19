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

char	*ft_strchr(const char *s, int c)
{
	char	*copy;

	copy = (char *) s;
	while (*copy != 0)
	{
		if (*copy == (char)c)
			return (copy);
		copy++;
	}
	if (*copy == (char)c)
		return (copy);
	return (NULL);
}

char	*ft_str(int fd, char *buff, char *str, int first)
{
	int		i;
	
	i = first;
	if (buff[i] == '\n')
		i++;
	if (buff[i] == 0){
		printf("Reading.");
		read(fd, buff, BUFFER_SIZE);
	}
	while (buff[i] != '\n' && buff[i] != 0)
		i++;
	//printf("-%c", buff[first]);
	if (str == NULL)
	{
		str = malloc(1);
		if (str == NULL)
			return (NULL);
		str[0] = 0;
	}
	printf("%d %d\n", first, i);
	str = ft_strjoin(str, ft_substr(buff, first, i - first + 1));
	//printf("\n-%s\n\n", buff);
	if (buff[i] == 0)
	{
		buff[0] = 0;
		return (ft_str(fd, buff, str, 0));
	}
	return (str);
}

int	ft_getn(char *buff)
{
	int	i;
	int	n;
	int	firstn;

	firstn = 0;
	n = 0;
	i = 1;
	while (buff[i] != 0)
	{
		if (buff[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buff = 0;
	char		*str;

	if (!ft_file_check(fd, buff))
		return (NULL);
	if(buff == 0)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buff == NULL)
			return (NULL);
		buff[BUFFER_SIZE] = 0;
		str = ft_str(fd, buff, NULL, 0);
	}
	else
		str = ft_str(fd, buff, NULL, ft_getn(buff));
	//printf("-%s-", buff);
	if (str == NULL)
	{
		free(buff);
		buff = NULL;
		return (NULL);
	}
	return (str);
}

#include <stdio.h>
int	main(int argc, char *argv[]){
	int	fd = open(argv[1], O_RDONLY, 0);
	int i = 0;
	while (i < 10){
		printf("%s", get_next_line(fd));
		i++;
	}
	return (argc);
}