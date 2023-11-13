/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:18:44 by jtollena          #+#    #+#             */
/*   Updated: 2023/11/13 15:34:12 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*ft_read(int fd, char **str)
{
	char	*buff;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	buff[BUFFER_SIZE] = 0;
	if(read(fd, buff, BUFFER_SIZE) <= 0)
	{
		free(*str);
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
	newline = malloc((i + 1) * sizeof(char));
	if (!newline)
		return (NULL);
	newline[i] = 0;
	ft_strlcpy(newline, s, i);
	return (newline);
}

char	*ft_newline(int fd, char **str)
{
	char	*newstr;
	char	*read;
	char	*tmp;
	
	if (!*str)
	{
		read = ft_read(fd, str);
		if (!read)
			return (NULL);
	}
	else
	{
		read = ft_strdup(*str);
		if (!read)
			return (NULL);
		free(*str);
		*str = NULL;
	}
	newstr = ft_getline(read);
	if (!newstr)
		return (free(read), NULL);
	while (ft_strchr(read, '\n') == -1)
	{
		free(read);
		read = ft_read(fd, str);
		if (!read)
		{
			free(*str);
			*str = NULL;
			break ;
		}
		tmp = ft_getline(read);
		newstr = ft_strjoin(newstr, tmp);
		free(tmp);
	}
	if (ft_strchr(read, '\n') >= 0)
		*str = ft_strdup(&read[ft_strchr(read, '\n') + 1]);
	if (ft_strlen(newstr) == 0)
	{
		free(newstr);
		return (NULL);
	}
	return (free(read), newstr);
}

char	*get_next_line(int fd)
{
	static char	*str[1025];
	char		*newline;

	if (fd < 0 || fd >= 1025)
		return (NULL);
	newline = ft_newline(fd, &str[fd]);
	if (newline == NULL)
		free(str[fd]);
	return (newline);
}

// #include <stdio.h>
// int	main(int argc, char *argv[]){
// 	int	fd = open(argv[1], O_RDONLY, 0);
// 	int i = 0;
// 	while (i < 4){
// 		printf("%s", get_next_line(fd));
// 		i++;
// 	}
// 	return (argc);
// }