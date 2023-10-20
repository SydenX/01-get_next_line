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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*srccpy;
	unsigned char		*copy;

	copy = dst;
	srccpy = src;
	if (dst == NULL && src == NULL)
		return (0);
	while (n > 0)
	{
		*copy = *srccpy;
		srccpy++;
		copy++;
		n--;
	}
	return (dst);
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
		if (copy[i] == (char)c)
			return (i);
		i++;
	}
	if (copy[i] == (char)c)
		return (i);
	return (-1);
}

char	*ft_ft(char *tmp, char *buff, int maxsub)
{
	char	*str;
	char	*substr;

	str = ft_strdup(tmp);
	if (str == NULL)
		return (NULL);
	free(tmp);
	substr = ft_substr(buff, 0, maxsub);
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
	// char	*str;
	char	*tmp;
	// char	*substr;

	tmp = ft_strdup("");
	if (tmp == NULL)
		return (NULL);
	while (ft_strchr(buff, '\n') == -1)
	{
		tmp = ft_ft(tmp, buff, ft_strlen(buff) + 1);
		// str = ft_strdup(tmp);
		// if (str == NULL)
		// {
		// 	free(tmp);
		// 	return (NULL);
		// }

		// substr = ft_substr(buff, 0, ft_strlen(buff) + 1);
		// if (substr == NULL)
		// {
		// 	free(str);
		// 	free(tmp);
		// 	return (NULL);
		// }
		// if (tmp[0] == 0)
		// 	free(tmp);
		// tmp = ft_strjoin(str, substr);
		// free(substr);
		// free(str);
		// if (tmp == NULL)
		// 	return (NULL);
		if(read(fd, buff, BUFFER_SIZE) <= 0)
		{
			free(buff);
			buff = NULL;
			return (tmp);
		}
	}
	tmp = ft_ft(tmp, buff, ft_strchr(buff, '\n') + 1);
	//printf("%s", buff);
	// str = ft_strdup(tmp);
	// if (str == NULL)
	// {
	// 	free(tmp);
	// 	return (NULL);
	// }

	// tmp = ft_strjoin(str, ft_substr(buff, 0, ft_strchr(buff, '\n') + 1));
	// free(str);
	// if (tmp == NULL)
	// 	return (NULL);
	// str = ft_strdup(tmp);
	// free(tmp);
	// if (str == NULL)
	// 	return (NULL);
	return (tmp);
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
		if(read(fd, buff, BUFFER_SIZE) <= 0)
		{
			free(buff);
			buff = NULL;
			return (NULL);
		}
		str = ft_str(fd, buff);
	}
	else
		str = ft_str(fd, buff);
	if(buff == NULL)
		return (NULL);
	if (str == NULL || str[0] == 0)
	{
		if(str[0] == 0)
			free(str);
		free(buff);
		buff = NULL;
		return (NULL);
	}
	if (buff == NULL)
	{
		free(buff);
		buff = NULL;
		return (0);
	}
	else if(ft_strchr(buff, '\n') == -1)
	{
		free(buff);
		buff = NULL;
		return (str);
	}
	else
		ft_memcpy(buff, &buff[ft_strchr(buff, '\n') + 1], ft_strlen(&buff[ft_strchr(buff, '\n') + 1]) + 1);
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