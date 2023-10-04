/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:15:17 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/20 12:44:47 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_raycasting(t_game *game)
{
	game->ray.x = 0;
	while (game->ray.x < game->rx)
	{
		ft_init3(game);
		ft_stepsidedist(game);
		ft_color_column(game);
		game->sp.zbuffer[game->ray.x] = game->ray.perpwalldist;
		game->ray.x++;
	}
	ft_sprite(game);
	mlx_put_image_to_window(game->data.mlx_ptr, game->data.mlx_win,
		game->data.img, 0, 0);
	print_minimap(game);
	ft_forward_back(game);
	ft_left_right(game);
	ft_rotate_right(game);
	ft_rotate_left(game);
	ft_swap(game);
	return (0);
}

//calcul de stepx, stepy, sidedistx et sidedisty
void	ft_stepsidedist(t_game *game)
{
	if (game->ray.raydirx < 0)
	{
		game->ray.stepx = -1;
		game->ray.sidedistx = (game->ray.posx - game->ray.mapx) \
							* game->ray.deltadistx;
	}
	else
	{
		game->ray.stepx = 1;
		game->ray.sidedistx = (game->ray.mapx + 1.0 - game->ray.posx) \
							* game->ray.deltadistx;
	}
	if (game->ray.raydiry < 0)
	{
		game->ray.stepy = -1;
		game->ray.sidedisty = (game->ray.posy - game->ray.mapy) \
							* game->ray.deltadisty;
	}
	else
	{
		game->ray.stepy = 1;
		game->ray.sidedisty = (game->ray.mapy + 1.0 - game->ray.posy) \
							* game->ray.deltadisty;
	}
	ft_incrementray(game);
}

int	ft_color_column(t_game *game)
{
	int	j;
	int	i;

	j = -1;
	i = game->ray.drawend;
	while (++j < game->ray.drawstart)
		game->data.addr[j * game->data.line_length / 4
			+ game->ray.x] = game->c;
	if (j <= game->ray.drawend)
		ft_draw_texture(game, game->ray.x, j);
	j = i;
	while (++j < game->ry)
		game->data.addr[j * game->data.line_length / 4
			+ game->ray.x] = game->f;
	return (0);
}
