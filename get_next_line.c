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

int	ft_strchr(const char *s, int c)
{
	char	*copy;
	int		i;

	i = 0;
	copy = (char *) s;
	while (*copy != 0)
	{
		if (*copy == (char)c)
			return (i);
		copy++;
		i++;
	}
	if (*copy == (char)c)
		return (i);
	return (-1);
}

char	*ft_str(int fd, char *buff, int first)
{
	char	*str;
	char	*tmp;

	tmp = ft_strdup("");
	if (tmp == NULL)
		return (NULL);
	while (ft_strchr(buff + first, '\n') == -1)
	{
		str = ft_strdup(tmp);
		if (str == NULL)
		{
			free(tmp);
			return (NULL);
		}
		tmp = ft_strjoin(str, ft_substr(buff + first, 0, ft_strlen(buff) + 1));
		free(str);
		if (tmp == NULL)
			return (NULL);
		first = 0;
		read(fd, buff, BUFFER_SIZE);
	}

	str = ft_strdup(tmp);
	if (str == NULL)
	{
		free(tmp);
		return (NULL);
	}
	tmp = ft_strjoin(str, ft_substr(buff, 0, ft_strchr(buff, '\n') + 1));
	free(str);
	if (tmp == NULL)
		return (NULL);

	str = ft_strdup(tmp);
	free(tmp);
	if (str == NULL)
		return (NULL);
	return (str);
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
		read(fd, buff, BUFFER_SIZE);
		str = ft_str(fd, buff, 0);
	}
	else
		str = ft_str(fd, buff, ft_strchr(buff, '\n') + 1);
	if (str == NULL)
	{
		free(buff);
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