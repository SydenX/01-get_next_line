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
	char	*buff;
	char	*str;
	int		readable;
	int		i;

	if (fd == -1)
		return (NULL);
	str = malloc(2);
	if (str == NULL)
		return (NULL);
	buff = malloc(BUFFER_SIZE);
	if (buff == NULL)
	{
		free(str);
		return (NULL);
	}
	readable = read(fd, str, 1);
	if (readable <= 0)
		return (NULL);
	i = 0;
	while (readable > 0)
	{
		if (str[0] == '\n'){
			if (i < BUFFER_SIZE && str[0] != 0)
				buff[i++] = str[0];
			break ;}
		if (i < BUFFER_SIZE && str[0] != 0)
		{
			buff[i] = str[0];
			i++;
		}
		else if (i >= BUFFER_SIZE)
			break ;
		readable = read(fd, str, 1);
	}
	buff[i] = 0;
	free(str);
	return (buff);
}

// #include <stdio.h>
// int	main(int argc, char *argv[]){
// 	int	fd = open(argv[1], O_RDONLY, 0);
// 	int i = 0;
// 	while (i++ < 4)
// 		printf("%s", get_next_line(fd));
// 	return (argc);
// }
