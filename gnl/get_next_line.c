/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:08:49 by bschwitz          #+#    #+#             */
/*   Updated: 2023/05/08 15:40:52 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_check(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_copy(char **line, char **buff)
{
	int		start;
	char	*temp;
	char	*line_temp;

	start = ft_check(*buff);
	if (start >= 0)
	{
		temp = ft_substr(*buff, 0, start);
		line_temp = *line;
		*line = ft_strjoin(*line, temp);
		free(temp);
		free(line_temp);
		*buff = ft_subbuff(*buff, start + 1, (ft_strlen(*buff) - start));
		return (0);
	}
	else
	{
		temp = NULL;
		ft_copy2(temp, line, buff);
		return (1);
	}
	return (-1);
}

void	ft_copy2(char *temp, char **line, char **buff)
{
	temp = NULL;
	if (*line)
		temp = *line;
	*line = ft_strjoin(*line, *buff);
	if (temp)
		free(temp);
}

int	ft_eof(int ret, char **buff, char **line)
{
	if (ret == -1)
		return (-1);
	free(*buff);
	*buff = NULL;
	if (*line == NULL)
	{
		*line = malloc(sizeof(char) * 1);
		*line[0] = 0;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*buff = NULL;
	int			ret;

	if (fd < 0 || BUFFER_SIZEGNL <= 0 || !line)
		return (-1);
	*line = NULL;
	ret = 1;
	if (buff)
		ret = ft_copy(line, &buff);
	if (ret == 0)
		return (1);
	if (!buff)
		buff = malloc(sizeof(char) * BUFFER_SIZEGNL + 1);
	if (!buff)
		return (-1);
	while (ret > 0)
	{
		ret = gnl2(ret, buff, fd);
		if (!ft_copy(line, &buff))
			return (1);
	}
	if (ret <= 0)
		return (ft_eof(ret, &buff, line));
	return (1);
}
