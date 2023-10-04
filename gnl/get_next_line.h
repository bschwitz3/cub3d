/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 18:09:16 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/20 12:52:30 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../cub3d.h"

# define BUFFER_SIZEGNL		30

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_subbuff(char *buff, int start, int len);
int		ft_check(char *str);
int		ft_copy(char **line, char **buff);
void	ft_copy2(char *temp, char **line, char **buff);
int		ft_eof(int ret, char **buff, char **line);
int		get_next_line(int fd, char **line);

int		gnl2(int ret, char *buff, int fd);

#endif