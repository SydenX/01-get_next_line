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

char	*get_next_line(int fd)
{
	static char *buff = NULL;

	if (fd < 0)
	{
		if (buff != NULL)
			free(buff);
		buff = NULL;
		return (NULL);
	}
	else
	if (buff == NULL)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buff == NULL)
			return (NULL);
	}
	return (buff);
}

// char	*get_next_lineold(int fd)
// {
// 	static char	*buff = 0;
// 	char		*str;
// 	static int	readable = 0;
// 	static int	i = 0;
// 	int			j;

// 	if (fd == -1)
// 	{
// 		if (buff != NULL)
// 		{	
// 			free(buff);
// 			buff = NULL;
// 		}
// 		return (NULL);
// 	}
// 	if (readable == 0)
// 	{
// 		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 		if (buff == NULL)
// 			return (NULL);
// 		buff[BUFFER_SIZE] = 0;
// 		readable = read(fd, buff, BUFFER_SIZE);
// 		if (readable < 1){
// 			free(buff);
// 			buff = NULL;
// 			return (NULL);
// 		}
// 	}
// 	if (buff == NULL)
// 		return (NULL);
// 	if (i >= BUFFER_SIZE)
// 	{
// 		readable = read(fd, buff, BUFFER_SIZE);
// 		if (readable < 1)
// 		{
// 			free(buff);
// 			buff = NULL;
// 			return (NULL);
// 		}
// 	}
// 	j = 0;
// 	while (buff[i + j] != 0 && buff[i + j] != '\n')
// 		j++;
// 	str = malloc((j + 1) * sizeof(char));
// 	if (str == NULL)
// 	{
// 		free(buff);
// 		buff = NULL;
// 		return (NULL);
// 	}
// 	j = 0;
// 	while (buff[i] != 0 && buff[i] != '\n')
// 	{
// 		str[j] = buff[i];
// 		i++;
// 		j++;
// 	}
// 	if (buff[i] == '\n')
// 		str[j] = '\n';
// 	else
// 		str[j] = 0;
// 	i++;
// 	return (str);
// }

// #include <stdio.h>
// int	main(int argc, char *argv[]){
// 	int	fd = open(argv[1], O_RDONLY, 0);
// 	int i = 0;
// 	while (i++ < 80)
// 		printf("%s", get_next_line(fd));
// 	return (argc);
// }