/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:24:05 by bschwitz          #+#    #+#             */
/*   Updated: 2023/05/08 15:54:02 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_map(char *str, t_game *game)
{
	int			i;
	static int	snblines = 0;
	static int	ssizeline = 0;

	i = 0;
	if (ft_mapstart(str))
		game->inmap = 1;
	if (ft_is_map(str) == 1)
	{
		i = ft_strlen(str);
		if (i > ssizeline)
			ssizeline = i;
		snblines++;
	}
	if (ft_is_map(str) == 0 && game->inmap == 1)
		ft_error(game, "Wrong char in map.");
	game->nbline = snblines;
	game->sizeline = ssizeline;
}

int	ft_is_map(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (ft_charinstr(str, '1') == 1)
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
				&& str[i] != '2' && str[i] != 'N' && str[i] != 'S' \
				&& str[i] != 'E' && str[i] != 'W' && str[i] != '\n'
				&& str[i] != '\t')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_copy_map(char *str, t_game *game)
{
	static int	i = 0;
	int			j;

	j = 0;
	game->map[i] = malloc(sizeof(char) * game->sizeline + 1);
	if (!game->map[i])
		return (0);
	while (str[j] != '\0')
	{
		if (ft_start(str[j], game, i, j) == 1)
			game->map[i][j] = '0';
		else if (str[j] == ' ')
			game->map[i][j] = '1';
		else
			game->map[i][j] = str[j];
		j++;
	}
	while (j <= (game->sizeline - 1))
	{
		game->map[i][j] = '1';
		j++;
	}
	game->map[i][j] = '\0';
	i++;
	return (0);
}

int	check_map(char *fichier, t_game *game)
{
	int		fd;
	int		ret;
	char	*str;

	str = NULL;
	ret = 1;
	fd = open(fichier, O_RDONLY);
	game->check = malloc(sizeof(char *) * game->nbline);
	if (!game->check)
		return (0);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		if (ft_is_map(str) == 1)
			ft_copy_check(str, game);
		free(str);
	}
	close(fd);
	check_map2(game);
	return (1);
}

void	check_map2(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	check_first_last(game);
	while (i < game->nbline)
	{
		j = 0;
		while (j < game->sizeline)
			check_close(i, j++, game);
		i++;
	}
}
