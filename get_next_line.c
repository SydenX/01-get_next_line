/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:39:41 by jtollena          #+#    #+#             */
/*   Updated: 2023/11/10 14:26:22 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int	ft_file_check(int fd)
{
	if (fd == -1)
		return (0);
	return (1);
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

char	*ft_getline(int fd, char **str)
{
	int		i;
	int		j;
	char	*buff;
	char	*newstr;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	buff[BUFFER_SIZE] = 0;
	if(read(fd, buff, BUFFER_SIZE) < 0)
	{
		free(buff);
		return (*str);
	}
	i = 0;
	j = i;
	while (buff[i] != 0)
	{
		if (buff[i++] == '\n')
			break ;
	}
	newstr = malloc((ft_strlen(*str) + i - j + 1) * sizeof(char));
	if (newstr == NULL)
	{
		free(buff);
		return (NULL);
	}
	printf("-> %s\n", *str);
	ft_strlcpy(newstr, &buff[j], i - j);

	if ((i == BUFFER_SIZE && buff[i - 1] != '\n'))
		newstr = ft_strjoin(newstr, ft_getline(fd, NULL));

	free(*str);
	*str = malloc((ft_strlen(&buff[i]) + 1) * sizeof(char));
	if (*str == NULL)
	{
		free(buff);
		free(newstr);
		return (NULL);
	}
	ft_strlcpy(*str, &buff[i], ft_strlen(&buff[i]));
	
	free(buff);
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char		*str[1025];
	int				i;
	char			*eline;
	char			*newstr;
	char			*tmp;

	if (!ft_file_check(fd))
		return (NULL);
	printf("%s", str[fd]);
	tmp = ft_strdup(str[fd]);
	if (!tmp)
	{
		free(str);
		return (NULL);
	}
	newstr = ft_getline(fd, &str[fd]);
	if (newstr == NULL)
	{
		free(str);
		free(tmp);
		return (NULL);
	}
	if (tmp)
		eline = ft_strjoin(tmp, newstr);
	else
		return (newstr);
	if (eline == NULL)
	{
		free(tmp);
		free(newstr);
		free(str);
		return (NULL);
	}
	return (eline);
}

#include <stdio.h>
int	main(int argc, char *argv[]){
	int	fd = open(argv[1], O_RDONLY, 0);
	int i = 0;
	while (i < 2){
		printf("%s", get_next_line(fd));
		i++;
	}
	return (argc);
}