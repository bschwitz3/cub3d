/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:50:38 by bschwitz          #+#    #+#             */
/*   Updated: 2023/05/05 11:21:41 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_copy_check(char *str, t_game *game)
{
	static int	i = 0;
	int			j;

	j = 0;
	game->check[i] = malloc(sizeof(char) * game->sizeline + 1);
	if (!game->check[i])
		return (0);
	while (str[j] != '\0')
	{
		game->check[i][j] = str[j];
		j++;
	}
	game->check[i][j] = '\0';
	i++;
	return (0);
}

void	check_close(int i, int j, t_game *game)
{
	if (game->check[i][j] == '0' || game->check[i][j] == '2'
		|| game->check[i][j] == 'W' || game->check[i][j] == 'N'
		|| game->check[i][j] == 'E' || game->check[i][j] == 'S')
	{
		if (game->check[i - 1][j] != '0' && game->check[i - 1][j] != '2'
			&& game->check[i - 1][j] != 'W' && game->check[i - 1][j] != 'N'
			&& game->check[i - 1][j] != 'E' && game->check[i - 1][j] != 'S'
			&& game->check[i - 1][j] != '1')
			ft_error(game, "Map isn't close.");
		if (game->check[i + 1][j] != '0' && game->check[i + 1][j] != '2'
			&& game->check[i + 1][j] != 'W' && game->check[i + 1][j] != 'N'
			&& game->check[i + 1][j] != 'E' && game->check[i + 1][j] != 'S'
			&& game->check[i + 1][j] != '1')
			ft_error(game, "Map isn't close.");
		if (game->check[i][j - 1] != '0' && game->check[i][j - 1] != '2'
			&& game->check[i][j - 1] != 'W' && game->check[i][j - 1] != 'N'
			&& game->check[i][j - 1] != 'E' && game->check[i][j - 1] != 'S'
			&& game->check[i][j - 1] != '1')
			ft_error(game, "Map isn't close.");
		if (game->check[i][j + 1] != '0' && game->check[i][j + 1] != '2'
			&& game->check[i][j + 1] != 'W' && game->check[i][j + 1] != 'N'
			&& game->check[i][j + 1] != 'E' && game->check[i][j + 1] != 'S'
			&& game->check[i][j + 1] != '1')
			ft_error(game, "Map isn't close.");
	}
}

int	ft_start(char c, t_game *game, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (game->depart != 'x')
			ft_error(game, "Plus d'un joueur dans la map");
		game->depart = c;
		game->dx = i;
		game->dy = j;
		return (1);
	}
	return (0);
}

int	ft_charinstr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_mapstart(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '1')
			j++;
		if (str[i] != '1' && str[i] != ' '
			&& str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	if (j < 1)
		return (0);
	return (1);
}
