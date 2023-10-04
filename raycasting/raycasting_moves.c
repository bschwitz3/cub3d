/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_moves.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:50:13 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/19 19:23:14 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_forward_back(t_game *game)
{
	if (game->data.forward == 1)
	{
		if (game->map[(int)(game->ray.posx + game->ray.dirx
				* game->ray.movespeed)][(int)game->ray.posy] == '0')
			game->ray.posx += game->ray.dirx * game->ray.movespeed;
		if (game->map[(int)(game->ray.posx)][(int)(game->ray.posy
				+ game->ray.diry * game->ray.movespeed)] == '0')
			game->ray.posy += game->ray.diry * game->ray.movespeed;
	}
	if (game->data.back == 1)
	{
		if (game->map[(int)(game->ray.posx - game->ray.dirx
				* game->ray.movespeed)][(int)(game->ray.posy)] == '0')
			game->ray.posx -= game->ray.dirx * game->ray.movespeed;
		if (game->map[(int)(game->ray.posx)][(int)(game->ray.posy
				- game->ray.diry * game->ray.movespeed)] == '0')
			game->ray.posy -= game->ray.diry * game->ray.movespeed;
	}
}

void	ft_left_right(t_game *game)
{
	if (game->data.right == 1)
	{
		if (game->map[(int)(game->ray.posx + game->ray.diry
				* game->ray.movespeed)][(int)game->ray.posy] == '0')
			game->ray.posx += game->ray.diry * game->ray.movespeed;
		if (game->map[(int)game->ray.posx][(int)(game->ray.posy - game->ray.dirx
			* game->ray.movespeed)] == '0')
			game->ray.posy -= game->ray.dirx * game->ray.movespeed;
	}
	if (game->data.left == 1)
	{
		if (game->map[(int)(game->ray.posx - game->ray.diry
				* game->ray.movespeed)][(int)game->ray.posy] == '0')
			game->ray.posx -= game->ray.diry * game->ray.movespeed;
		if (game->map[(int)game->ray.posx][(int)(game->ray.posy + game->ray.dirx
			* game->ray.movespeed)] == '0')
			game->ray.posy += game->ray.dirx * game->ray.movespeed;
	}
}

void	ft_rotate_right(t_game *game)
{
	double	olddirx;
	double	oldplanx;

	if (game->data.rotate_right == 1)
	{
		olddirx = game->ray.dirx;
		game->ray.dirx = game->ray.dirx * cos(-game->ray.rotspeed / 2)
			- game->ray.diry * sin(-game->ray.rotspeed / 2);
		game->ray.diry = olddirx * sin(-game->ray.rotspeed / 2)
			+ game->ray.diry * cos(-game->ray.rotspeed / 2);
		oldplanx = game->ray.planx;
		game->ray.planx = game->ray.planx * cos(-game->ray.rotspeed / 2)
			- game->ray.plany * sin(-game->ray.rotspeed / 2);
		game->ray.plany = oldplanx * sin(-game->ray.rotspeed / 2)
			+ game->ray.plany * cos(-game->ray.rotspeed / 2);
	}
}

void	ft_rotate_left(t_game *game)
{
	double	olddirx;
	double	oldplanx;

	if (game->data.rotate_left == 1)
	{
		olddirx = game->ray.dirx;
		game->ray.dirx = game->ray.dirx * cos(game->ray.rotspeed / 2)
			- game->ray.diry * sin(game->ray.rotspeed / 2);
		game->ray.diry = olddirx * sin(game->ray.rotspeed / 2)
			+ game->ray.diry * cos(game->ray.rotspeed / 2);
		oldplanx = game->ray.planx;
		game->ray.planx = game->ray.planx * cos(game->ray.rotspeed / 2)
			- game->ray.plany * sin(game->ray.rotspeed / 2);
		game->ray.plany = oldplanx * sin(game->ray.rotspeed / 2)
			+ game->ray.plany * cos(game->ray.rotspeed / 2);
	}
}
