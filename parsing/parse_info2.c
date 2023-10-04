/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 16:09:10 by bschwitz          #+#    #+#             */
/*   Updated: 2023/05/04 11:37:10 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	*ft_atoi_f(const char *str, t_game *game)
{
	int	t;
	int	temp;

	temp = game->indic2;
	t = -1;
	game->verifyf = 0;
	game->sumf = 0;
	if (str[1] != ' ')
		ft_error(game, "Identifiant F incorrect\n");
	while (str[game->i] == ' ' || str[game->i] == '\t' || str[game->i]
		== ',' || str[game->i] == '\n' || str[game->i] == '\r'
		|| str[game->i] == '\v' || str[game->i] == '\f')
	{
		game->i++;
		game->verifyf = 0;
		if (str[game->i] >= '0' && str[game->i] <= '9')
		{
			game->indic2++;
			t++;
		}
		temp = ft_atoi_f2(game, temp, str, t);
	}
	if (t != 2)
		ft_error(game, "Wrong rgb data for F.");
	return (game->floor);
}

int	ft_atoi_f2(t_game *game, int temp, const char *str, int t)
{
	while (str[game->i] >= '0' && str[game->i] <= '9')
	{
		game->verifyf = (game->verifyf * 10) + str[game->i] - 48;
		game->sumf = (game->sumf * 10) + (str[game->i] - 48);
		game->i++;
	}
	if (game->verifyf > 255)
		ft_error(game, "Number higher than 255 in F\n");
	if (temp < game->indic2)
	{
		game->floor[t] = game->verifyf;
		temp = game->indic2;
	}
	return (temp);
}

int	*ft_atoi_c(const char *str, t_game *game)
{
	int		t;
	int		temp;

	temp = game->indic2;
	t = -1;
	game->verifyc = 0;
	game->sumc = 0;
	if (str[1] != ' ')
		ft_error(game, "Identifiant C incorrect\n");
	while (str[game->i] == ' ' || str[game->i] == '\t' || str[game->i]
		== ',' || str[game->i] == '\n' || str[game->i] == '\r'
		|| str[game->i] == '\v' || str[game->i] == '\f')
	{
		game->i++;
		game->verifyc = 0;
		if (str[game->i] >= '0' && str[game->i] <= '9')
		{
			game->indic2++;
			t++;
		}
		temp = ft_atoi_c2(game, temp, str, t);
	}
	if (t != 2)
		ft_error(game, "Wrong rgb data for C.");
	return (game->ceiling);
}

int	ft_atoi_c2(t_game *game, int temp, const char *str, int t)
{
	while (str[game->i] >= '0' && str[game->i] <= '9')
	{
		game->verifyc = (game->verifyc * 10) + str[game->i] - 48;
		game->sumc = (game->sumc * 10) + (str[game->i] - 48);
		game->i++;
	}
	if (game->verifyc > 255)
		ft_error(game, "Number higher than 255 in C\n");
	if (temp < game->indic2)
	{
		game->ceiling[t] = game->verifyc;
		temp = game->indic2;
	}
	return (temp);
}

void	default_fc(t_game *game)
{
	if (!game->f)
	{
		game->f = GROUND;
		write(1, "No color for F, default set black.\n", 36);
	}
	if (!game->c)
	{
		game->c = CEILING;
		write(1, "No color for C, default set sky blue.\n", 39);
	}
}
