/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:18:44 by jtollena          #+#    #+#             */
/*   Updated: 2023/11/16 11:46:37 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	ln;

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
	while (buff[i] != 0 && buff[i] != '\n')
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

char	*ft_readbuff(char *buff)
{
	char	*newline;
	int		i;

	i = 0;
	if (!buff[i])
		return (NULL);
	while (buff[i] && buff[i] != '\n')
		i++;
	if (buff[i] == '\n')
		i++;
	newline = malloc((i + 1) * sizeof(char));
	if (newline == NULL)
		{free(buff); buff = NULL; return (NULL);}
	i = 0;
	while (buff[i] != 0 && buff[i] != '\n')
	{
		newline[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
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
	static char	*buff[1025];
	char		*newline;

	if (fd < 0 || fd >= 1025 || read(fd, 0, 0) < 0)
	{
		if (buff[fd] != 0)
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
	if (!buff[fd])
		return (NULL);
	newline = ft_readbuff(buff[fd]);
	if(buff[fd] != NULL)
		buff[fd] = ft_updatebuff(buff[fd]);
	return (newline);
}

// #include <stdio.h>
// int	main(int argc, char *argv[]){
// 	int	fd = open(argv[1], O_RDONLY, 0);
// 	//int	fd2 = open(argv[2], O_RDONLY, 0);
// 	int i = 0;
// 	while (i < 20){
// 		printf("-%s\n", get_next_line(fd));
// 		//printf("-%s\n", get_next_line(fd2));
// 		i++;
// 	}
// 	return (argc);
// }