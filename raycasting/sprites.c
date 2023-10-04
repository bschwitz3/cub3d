/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:45:36 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/20 12:23:40 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_dist_order(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->sp.nbspr)
	{
		game->sp.order[i] = i;
		game->sp.dist[i] = ((game->ray.posx - game->sxy[i].x)
				* (game->ray.posx - game->sxy[i].x) + (game->ray.posy
					- game->sxy[i].y) * (game->ray.posy - game->sxy[i].y));
		i++;
	}
	ft_dist_order2(game);
}

void	ft_dist_order2(t_game *game)
{
	int		i;
	int		j;
	double	tmp;

	i = 0;
	while (i < game->sp.nbspr)
	{
		j = 0;
		while (j < game->sp.nbspr - 1)
		{
			if (game->sp.dist[j] < game->sp.dist[j + 1])
			{
				tmp = game->sp.dist[j];
				game->sp.dist[j] = game->sp.dist[j + 1];
				game->sp.dist[j + 1] = tmp;
				tmp = game->sp.order[j];
				game->sp.order[j] = game->sp.order[j + 1];
				game->sp.order[j + 1] = (int)tmp;
			}
			j++;
		}
		i++;
	}
}

void	ft_calculs(t_game *game, int i)
{
	game->sp.spritex = game->sxy[game->sp.order[i]].x - game->ray.posx;
	game->sp.spritey = game->sxy[game->sp.order[i]].y - game->ray.posy;
	game->sp.invdet = 1.0 / (game->ray.planx
			* game->ray.diry - game->ray.dirx * game->ray.plany);
	game->sp.transformx = game->sp.invdet * (game->ray.diry
			* game->sp.spritex - game->ray.dirx * game->sp.spritey);
	game->sp.transformy = game->sp.invdet * (-game->ray.plany
			* game->sp.spritex + game->ray.planx * game->sp.spritey);
	game->sp.spritescreenx = (int)((game->rx / 2)
			* (1 + game->sp.transformx / game->sp.transformy));
	game->sp.spriteheight = abs((int)(game->ry / (game->sp.transformy)));
	game->sp.drawstarty = -game->sp.spriteheight / 2 + game->ry / 2;
	if (game->sp.drawstarty < 0)
		game->sp.drawstarty = 0;
	game->sp.drawendy = game->sp.spriteheight / 2 + game->ry / 2;
	if (game->sp.drawendy >= game->ry)
		game->sp.drawendy = game->ry;
	game->sp.spritewidth = abs((int)(game->ry / (game->sp.transformy)));
	game->sp.drawstartx = -game->sp.spritewidth / 2 + game->sp.spritescreenx;
	if (game->sp.drawstartx < 0)
		game->sp.drawstartx = 0;
	game->sp.drawendx = game->sp.spritewidth / 2 + game->sp.spritescreenx;
	if (game->sp.drawendx >= game->rx)
		game->sp.drawendx = game->rx;
}

void	ft_draw_spr(t_game *game, int y, int texX, int stripe)
{
	int		d;
	int		texy;

	while (y < game->sp.drawendy)
	{
		d = (y) * 256 - game->ry * 128 + game->sp.spriteheight * 128;
		texy = ((d * game->texture[4].height) / game->sp.spriteheight) / 256;
		if (game->texture[4].addr[texy * game->texture[4].line_length
				/ 4 + texX] != 000)
			game->data.addr[y * game->data.line_length / 4 + stripe]
				= game->texture[4].addr[texy * game->texture[4].line_length
				/ 4 + texX];
		y++;
	}
}

void	ft_sprite(t_game *game)
{
	int	i;
	int	y;
	int	stripe;
	int	texx;

	i = 0;
	ft_dist_order(game);
	while (i < game->sp.nbspr)
	{
		ft_calculs(game, i++);
		stripe = game->sp.drawstartx;
		while (stripe < game->sp.drawendx)
		{
			texx = (int)(256 * (stripe - (-game->sp.spritewidth / 2
							+ game->sp.spritescreenx)) * game->texture[4].width
					/ game->sp.spritewidth) / 256;
			if (game->sp.transformy > 0 && stripe >= 0 && stripe < game->rx
				&& game->sp.transformy < game->sp.zbuffer[stripe])
			{
				y = game->sp.drawstarty;
				ft_draw_spr(game, y, texx, stripe);
			}
			stripe++;
		}	
	}
}
