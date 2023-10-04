/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:42:30 by bschwitz          #+#    #+#             */
/*   Updated: 2023/05/08 16:18:12 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init22(t_game *game)
{
	if (game->depart == 'N')
		game->ray.dirx = -1;
	if (game->depart == 'S')
		game->ray.dirx = 1;
	if (game->depart == 'E')
		game->ray.diry = 1;
	if (game->depart == 'W')
		game->ray.diry = -1;
	if (game->depart == 'N')
		game->ray.plany = 0.66;
	if (game->depart == 'S')
		game->ray.plany = -0.66;
	if (game->depart == 'E')
		game->ray.planx = 0.66;
	if (game->depart == 'W')
		game->ray.planx = -0.66;
}

void	ft_init3(t_game *game)
{
	game->ray.hit = 0;
	game->ray.perpwalldist = 0;
	game->ray.camerax = 2 * game->ray.x / (double)game->rx - 1;
	game->ray.raydirx = game->ray.dirx + game->ray.planx * \
						game->ray.camerax;
	game->ray.raydiry = game->ray.diry + game->ray.plany * \
						game->ray.camerax;
	game->ray.mapx = (int)game->ray.posx;
	game->ray.mapy = (int)game->ray.posy;
	game->ray.movespeed = 0.1;
	game->ray.rotspeed = 0.033 * 1.8;
	if (game->ray.raydiry == 0)
		game->ray.deltadistx = 0;
	else if (game->ray.raydirx == 0)
		game->ray.deltadistx = 1;
	else
		game->ray.deltadistx = sqrt(1 + (game->ray.raydiry * game->ray.raydiry)
				/ (game->ray.raydirx * game->ray.raydirx));
	if (game->ray.raydirx == 0)
		game->ray.deltadisty = 0;
	else if (game->ray.raydiry == 0)
		game->ray.deltadisty = 1;
	else
	game->ray.deltadisty = sqrt(1 + (game->ray.raydirx * game->ray.raydirx)
				/ (game->ray.raydiry * game->ray.raydiry));
}

void	check_first_last(t_game *game)
{
	int	i;
	int	temp;

	temp = ft_strlen(game->check[0]);
	i = 0;
	while (i < temp)
	{
		if (game->check[0][i] != '1' && game->check[0][i] != ' ' &&
			game->check[0][i] != '\n')
			ft_error(game, "First line should only have '1'.");
		else
			i++;
	}
	i = 0;
	temp = ft_strlen(game->check[game->nbline - 1]);
	while (i < temp)
	{
		if (game->check[game->nbline - 1][i] != '1' &&
			game->check[game->nbline - 1][i] != ' ' &&
			game->check[game->nbline - 1][i] != '\n')
			ft_error(game, "Last line should only have '1'.");
		i++;
	}
}
