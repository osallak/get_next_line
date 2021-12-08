/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 21:00:52 by messalih          #+#    #+#             */
/*   Updated: 2021/12/08 17:31:01 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_remainder(char *buffer)
{
	int		i;
	int		x;
	char	*remainder;

	i = 0;
	x = 0;
	if (!*buffer)
		return (free(buffer), NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	remainder = malloc((ft_strlen(buffer) - i) * sizeof(char) + 1);
	if (remainder == NULL)
		return (NULL);
	while (buffer[i] != '\0')
		remainder[x++] = buffer[i++];
	remainder[x] = '\0';
	free(buffer);
	return (remainder);
}

static	char	*get_line(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!*buffer)
		return (NULL);
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	str = malloc(i * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		str[i++] = '\n';
	str[i] = '\0';
	return (str);
}

static	char	*get_buff(int fd, char *remainder)
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
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_strchr(remainder, '\n'))
		remainder = get_buff(fd, remainder);
	if (!remainder)
		return (NULL);
	line = get_line(remainder);
	remainder = get_remainder(remainder);
	return (line);
}
