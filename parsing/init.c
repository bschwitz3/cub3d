/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:16:52 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/24 19:40:21 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_init(t_game *game)
{
	game->no = NULL;
	game->so = NULL;
	game->we = NULL;
	game->ea = NULL;
	game->s = NULL;
	game->f = 0;
	game->floor = (int *)malloc(sizeof(int) * 4);
	if (!game->floor)
		ft_error(game, "Malloc game->floor");
	game->c = 0;
	game->ceiling = (int *)malloc(sizeof(int) * 4);
	if (!game->ceiling)
		ft_error(game, "Malloc game->ceiling");
	game->rx = 0;
	game->ry = 0;
	game->nbline = 0;
	game->sizeline = 0;
	game->map = NULL;
	game->dx = 0;
	game->dy = 0;
	game->depart = 'x';
	game->indic2 = 0;
	game->inmap = 0;
	ft_init_help(game);
}

void	ft_init_help(t_game *game)
{
	game->data.img = NULL;
	game->texture[0].img = NULL;
	game->texture[1].img = NULL;
	game->texture[2].img = NULL;
	game->texture[3].img = NULL;
	game->texture[4].img = NULL;
	game->data.mlx_win = NULL;
	game->map = NULL;
	game->check = NULL;
	game->sp.order = NULL;
	game->sp.dist = NULL;
}

void	ft_init_sprite(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	game->sp.nbspr = 0;
	ft_verify_errors(game);
	while (++i < game->nbline)
	{
		j = -1;
		while (++j < game->sizeline)
		{
			if (game->map[i][j] == '2')
				game->sp.nbspr += 1;
		}
	}
	game->sxy = (t_sprxy *)malloc(sizeof(t_sprxy) * game->sp.nbspr);
	if (!game->sxy)
		ft_error(game, "Malloc sxy*");
	game->sp.order = (int *)malloc(sizeof(int) * game->sp.nbspr);
	if (!game->sp.order)
		ft_error(game, "Malloc s.order*");
	game->sp.dist = (double *)malloc(sizeof(double) * game->sp.nbspr);
	if (!game->sp.dist)
		ft_error(game, "Malloc s.dist*");
	ft_init_sprite2(game, 0, 0, 0);
}

void	ft_init_sprite2(t_game *game, int i, int j, int v)
{
	i = i - 1;
	while (++i < game->nbline)
	{
		j = -1;
		while (++j < game->sizeline)
		{
			if (game->map[i][j] == '2')
			{
				game->sxy[v].x = (double)i + 0.5;
				game->sxy[v].y = (double)j + 0.5;
				v++;
			}
		}
	}
}

void	ft_init2(t_game *game)
{
	game->sp.zbuffer = (double *)malloc(sizeof(double) * game->rx);
	if (!game->sp.zbuffer)
		exit(0);
	game->data.forward = 0;
	game->data.back = 0;
	game->data.left = 0;
	game->data.right = 0;
	game->data.rotate_right = 0;
	game->data.rotate_left = 0;
	game->data.minimap = 0;
	game->ray.posx = (double)game->dx;
	game->ray.posy = (double)game->dy;
	game->ray.dirx = 0;
	game->ray.diry = 0;
	game->ray.planx = 0;
	game->ray.plany = 0;
	ft_init22(game);
}
