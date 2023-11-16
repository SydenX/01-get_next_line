/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:18:44 by jtollena          #+#    #+#             */
/*   Updated: 2023/11/16 14:28:14 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *s)
{
	int	ln;

	if (!s)
		return (0);
	ln = 0;
	while (s[ln] != 0)
		ln++;
	return (ln);
}

char	*ft_updatebuff(char *buff)
{
	char	*newbuff;
	int		i;
	int		j;

	i = 0;
	if (buff == NULL)
		return (NULL);
	while (buff[i] != '\n' && buff[i] != 0)
		i++;
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	newbuff = malloc((ft_strlen(buff) - i) * sizeof(char));
	if (newbuff == NULL)
		return (free(buff), NULL);
	newbuff[ft_strlen(buff) - i - 1] = 0;
	j = 0;
	i++;
	while (buff[i])
		newbuff[j++] = buff[i++];
	free(buff);
	return (newbuff);
}

char	*ft_readbuff(char **buff, int fd)
{
	char	*newline;
	int		i;

	i = 0;
	if (!buff[fd][i])
		return (NULL);
	while (buff[fd][i] && buff[fd][i] != '\n')
		i++;
	if (buff[fd][i] == '\n')
		i++;
	newline = malloc((i + 1) * sizeof(char));
	if (newline == NULL)
		return (free(buff[fd]), buff[fd] = NULL, NULL);
	i = 0;
	while (buff[fd][i] != 0 && buff[fd][i] != '\n')
	{
		newline[i] = buff[fd][i];
		i++;
	}
	if (buff[fd][i] == '\n')
		newline[i++] = '\n';
	newline[i] = 0;
	return (newline);
}

char	*ft_loadbuff(int fd, char *buff)
{
	char	*reader;
	int		readable;

	reader = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (reader == NULL)
	{
		free(buff);
		return (NULL);
	}
	readable = 1;
	while (!ft_strchr(buff, '\n') && readable != 0)
	{
		readable = read(fd, reader, BUFFER_SIZE);
		if (readable == -1)
		{
			free(reader);
			return (NULL);
		}
		reader[readable] = 0;
		buff = ft_strjoin(buff, reader);
		if (buff == NULL)
			return (NULL);
	}
	free(reader);
	return (buff);
}

char	*get_next_line(int fd)
{
	static char	*buff[1024];
	char		*newline;

	if (fd < 0 || fd > 1024 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		if (buff[fd] != NULL)
		{
			free(buff[fd]);
			buff[fd] = NULL;
		}
		return (NULL);
	}
	if (buff[fd] == NULL)
	{
		buff[fd] = malloc(1 * sizeof(char));
		if (buff[fd] == NULL)
			return (NULL);
		buff[fd][0] = 0;
	}
	buff[fd] = ft_loadbuff(fd, buff[fd]);
	if (buff[fd] == NULL)
		return (NULL);
	newline = ft_readbuff(buff, fd);
	buff[fd] = ft_updatebuff(buff[fd]);
	return (newline);
}

// #include <stdio.h>
// int	main(int argc, char *argv[]){
// 	int	fd = open(argv[1], O_RDONLY, 0);
// 	//int	fd2 = open(argv[2], O_RDONLY, 0);
// 	int i = 0;
// 	while (i < 2){
// 		printf("%s", get_next_line(fd));
// 		//printf("-%s\n", get_next_line(fd2));
// 		i++;
// 	}
// 	return (argc);
// }