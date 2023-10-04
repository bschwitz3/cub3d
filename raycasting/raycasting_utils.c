/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:35:34 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/20 12:18:20 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//tant qu'on a pas touche un mur on passe au carre suivant soit 
// dans la direction x soit direction y
void	ft_incrementray(t_game *game)
{
	while (game->ray.hit == 0)
	{
		if (game->ray.sidedistx < game->ray.sidedisty)
		{
			game->ray.sidedistx += game->ray.deltadistx;
			game->ray.mapx += game->ray.stepx;
			game->ray.side = 0;
		}
		else
		{
			game->ray.sidedisty += game->ray.deltadisty;
			game->ray.mapy += game->ray.stepy;
			game->ray.side = 1;
		}
		if (game->map[game->ray.mapx][game->ray.mapy] == '1')
			game->ray.hit = 1;
	}
	ft_drawstartend(game);
}

void	ft_drawstartend(t_game *game)
{
	if (game->ray.side == 0)
		game->ray.perpwalldist = ((double)game->ray.mapx - \
		game->ray.posx + (1 - (double)game->ray.stepx) / 2) / game->ray.raydirx;
	else
			game->ray.perpwalldist = ((double)game->ray.mapy - \
		game->ray.posy + (1 - (double)game->ray.stepy) / 2) / game->ray.raydiry;
	game->ray.lineheight = (int)(game->ry / game->ray.perpwalldist);
	game->ray.drawstart = -game->ray.lineheight / 2 + game->ry / 2;
	if (game->ray.drawstart < 0)
		game->ray.drawstart = 0;
	game->ray.drawend = game->ray.lineheight / 2 + game->ry / 2;
	if (game->ray.drawend >= game->ry || game->ray.drawend < 0)
		game->ray.drawend = game->ry - 1;
}

void	ft_swap(t_game *game)
{
	void	*tmp;

	tmp = game->data.img;
	game->data.img = game->data.img2;
	game->data.img2 = tmp;
	tmp = game->data.addr;
	game->data.addr = game->data.addr2;
	game->data.addr2 = tmp;
}
