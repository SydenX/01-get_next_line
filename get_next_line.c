/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:39:41 by jtollena          #+#    #+#             */
/*   Updated: 2023/10/24 11:49:16 by jtollena         ###   ########.fr       */
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
			return (tmp);
	}
	tmp = ft_subbuff(tmp, buff, ft_strchr(buff, '\n') + 1);
	return (tmp);
}

char	*ft_getline(int fd, char *str)
{
	int		i;
	int		j;
	char	*buff;
	char	*newstr;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buff == NULL)
		return (NULL);
	if(read(fd, buff, BUFFER_SIZE) <= 0)
		return (str);
	while (buff[i] == str[i])
		i++;
	j = i;
	while (buff[i] != 0 && buff[i] != '\n')
		i++;
	newstr = malloc((i - j) * sizeof(char));
	if (newstr == NULL)
	{
		free(buff);
		return (NULL);
	}
	ft_strlcpy(newstr, &buff[j], j - i);
	return (newstr);
}

char	*get_next_line(int fd)
{
	static char		*str;
	int				i;
	char			*eline;
	char			*newstr;

	if (!ft_file_check(fd))
		return (NULL);
	newstr = ft_getline(fd, str);
	if (newstr == NULL)
	{
		free(str);
		return (NULL);
	}
	eline = ft_strjoin(str, newstr);
	if (eline == NULL)
	{
		free(newstr);
		free(str);
		return (NULL);
	}
	return (str);
}

// #include <stdio.h>
// int	main(int argc, char *argv[]){
// 	int	fd = open(argv[1], O_RDONLY, 0);
// 	int i = 0;
// 	while (i < 12){
// 		printf("%s", get_next_line(fd));
// 		i++;
// 	}
// 	return (argc);
// }