/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:29:29 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/20 12:52:48 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (start < (unsigned int)ft_strlen((char *)s))
	{
		while (s[start] != '\0' && i < len)
		{
			str[i] = s[start];
			i++;
			start++;
		}
	}
	str[i] = '\0';
	return (str);
}

char	*ft_subbuff(char *buff, int start, int len)
{
	int		i;
	char	*str;

	str = NULL;
	str = ft_strjoin(str, buff);
	i = 0;
	while (str[i] != '\0' && i < len)
	{
		buff[i] = str[start];
		i++;
		start++;
	}
	buff[i] = 0;
	free(str);
	return (buff);
}

int	gnl2(int ret, char *buff, int fd)
{
	ret = read(fd, buff, BUFFER_SIZEGNL);
	buff[ret] = '\0';
	return (ret);
}
