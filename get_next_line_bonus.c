/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:07:12 by messalih          #+#    #+#             */
/*   Updated: 2021/12/09 01:04:23 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*get_remainder(char *buffer)
{
	int		i;
	int		j;
	char	*remainder;

	i = 0;
	j = 0;
	if (!*buffer)
		return (free(buffer), NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	remainder = malloc((ft_strlen(buffer) - i) * sizeof(char) + 1);
	if (!remainder)
		return (NULL);
	while (buffer[i])
		remainder[j++] = buffer[i++];
	remainder[j] = '\0';
	return (free(buffer), remainder);
}

static char	*get_line(char *remainder)
{
	int		i;
	char	*line;

	i = 0;
	if (!*remainder)
		return (NULL);
	while (remainder[i] != '\n' && remainder[i])
		i++;
	if (remainder[i] == '\n')
		i++;
	line = malloc(i * sizeof(char) + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] != '\n' && remainder[i])
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*read_buffer(int fd, char *remainder)
{
	char	*buff;
	int		i;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	i = 1;
	while (!ft_strchr(remainder, '\n') && i)
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			return (free(buff), NULL);
		buff[i] = '\0';
		remainder = ft_strjoin(remainder, buff);
	}
	return (free(buff), remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder[65535];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_strchr(remainder[fd], '\n'))
		remainder[fd] = read_buffer(fd, remainder[fd]);
	if (!remainder[fd])
		return (NULL);
	line = get_line(remainder[fd]);
	remainder[fd] = get_remainder(remainder[fd]);
	return (line);
}
