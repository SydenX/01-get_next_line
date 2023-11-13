/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:39:41 by jtollena          #+#    #+#             */
/*   Updated: 2023/11/13 12:39:18 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int	ft_file_check(int fd)
{
	if (fd < 0 || fd >= 1025)
		return (0);
	return (1);
}

char	*ft_newgetline(char *buff)
{
	int		i;
	char	*newstr;

	i = 0;
	if (!buff)
		return (NULL);
	while (buff[i] != 0)
	{
		if (buff[i++] == '\n')
			break ;
	}
	newstr = malloc((i + 1) * sizeof(char));
	if (newstr == NULL)
	{
		free(buff);
		return (NULL);
	}
	if (i == 0)
	{
		free(newstr);
		return (NULL);
	}
	ft_strlcpy(newstr, buff, i);
	return (newstr);
}

char	*ft_getline(int fd, char **str)
{
	int		i;
	char	*buff;
	char	*newstr;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	buff[BUFFER_SIZE] = 0;
	if(read(fd, buff, BUFFER_SIZE) <= 0)
	{
		free(buff);
		return (*str);
	}
	newstr = ft_newgetline(buff);
	if (newstr == NULL)
	{
		free(buff);
		return (NULL);
	}

	i = 0;
	while (buff[i] != 0)
	{
		if (buff[i++] == '\n')
			break ;
	}
	if ((i == BUFFER_SIZE && buff[i - 1] != '\n'))
	{
		free(buff);
		return (ft_strjoin(newstr, ft_getline(fd, str)));
	}

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

char	*ft_firststate(int fd, char **str)
{
	char	*newstr;
	char	*tmp;

	if (*str != NULL && BUFFER_SIZE > 1)
		newstr = ft_newgetline(*str);
	else
		newstr = ft_strdup("");
	if (newstr == NULL)
		return (NULL);
	if (ft_strlen(newstr) > 0)
	{
		if (newstr[ft_strlen(newstr) - 1] == '\n')
		{
			tmp = ft_strdup(*str);
			if(tmp == NULL)
				return (NULL);
			free(*str);
			*str = malloc((ft_strlen(tmp) - ft_strlen(newstr) + 1) * sizeof(char));
			if (*str == NULL)
			{
				free(tmp);
				return (NULL);
			}
			ft_strlcpy(*str, &tmp[ft_strlen(newstr)], ft_strlen(&tmp[ft_strlen(newstr)]));
			free(tmp);
			//printf("-> %s\n", *str);
			return (newstr);
		}
	}
	return (ft_strjoin(newstr, ft_getline(fd, str)));
}

char	*get_next_line(int fd)
{
	static char		*str[1025];
	char			*newstr;

	if (!ft_file_check(fd))
		return (NULL);

	newstr = ft_firststate(fd, &str[fd]);
	if (newstr == NULL)
	{
		free(str[fd]);
		return (NULL);
	}
	if (ft_strlen(newstr) == 0)
	{
		free(newstr);
		return (NULL);
	}
	return (newstr);
	// return (ft_strdup(""));
}

// #include <stdio.h>
// int	main(int argc, char *argv[]){
// 	int	fd = open(argv[1], O_RDONLY, 0);
// 	int i = 0;
// 	while (i < 2){
// 		printf("%s", get_next_line(fd));
// 		i++;
// 	}
// 	return (argc);
// }