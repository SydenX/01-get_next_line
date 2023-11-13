/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:18:44 by jtollena          #+#    #+#             */
/*   Updated: 2023/11/13 14:22:55 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*ft_read(int fd)
{
	char	*buff;

	buff = calloc((BUFFER_SIZE + 1), sizeof(char));
	if (buff == NULL)
		return (NULL);
	if(read(fd, buff, BUFFER_SIZE) <= 0)
	{
		free(buff);
		return (NULL);
	}
	return (buff);
}

char	*ft_getline(char *s)
{
	int		i;
	char	*newline;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != 0)
	{
		if (s[i++] == '\n')
			break ;
	}
	newline = calloc((i + 1), sizeof(char));
	if (!newline)
		return (NULL);
	return (ft_strlcpy(newline, s, i), newline);
}

char	*ft_ff(int fd, char *read)
{
	char	*newstr;
	return (newstr);
}

char	*ft_newline(int fd, char **str)
{
	char	*tmp;
	char	*newstr;
	char	*read;

	if (!*str)
	{
		read = ft_read(fd);
		if (!read)
			return (NULL);
	}
	else
	{
		read = ft_strdup(*str);
		if (!read)
			return (NULL);
		free(*str);
	}
	newstr = ft_getline(read);
	if (!newstr)
		return (free(read), NULL);
	while (ft_strchr(read, '\n') == -1)
	{
		read = ft_read(fd);
		newstr = ft_strjoin(newstr, ft_getline(read));
	}
	*str = ft_substr(read, ft_strchr(read, '\n'), ft_strlen(&read[ft_strchr(read, '\n')]));
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char	*str[1025];

	if (fd < 0 || fd >= 1025)
		return (NULL);
	return (ft_newline(fd, str));
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