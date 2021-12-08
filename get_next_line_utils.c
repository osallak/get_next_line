/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osallak <osallak@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 20:39:33 by messalih          #+#    #+#             */
/*   Updated: 2021/12/08 16:45:39 by osallak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	c;

	if (!str)
		return (0);
	c = 0;
	while (str[c] != '\0')
		c++;
	return (c);
}

int	ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char) c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		c;
	char	*str;
	int		len;
	int		str_len;

	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		s1[0] = '\0';
	}
	len = ft_strlen(s1);
	str_len = ft_strlen(s2);
	str = (char *)malloc((len + str_len) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	i = -1;
	c = 0;
	while (++i < len)
		str[i] = s1[i];
	while (c < str_len)
		str[i++] = s2[c++];
	str[i] = '\0';
	return (free(s1), str);
}