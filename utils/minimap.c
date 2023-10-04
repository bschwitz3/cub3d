/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:16:16 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/20 01:08:00 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	print_minimap(t_game *game)
{	
	int	x;
	int	y;

	if (game->data.minimap == 1)
	{
		x = 0;
		while (x < game->nbline)
		{
			y = 0;
			while (y < game->sizeline)
			{
				if (game->map[x][y] == '1')
					put_case(x, y, WALL, game);
				else if (game->map[x][y] == '0')
					put_case(x, y, GROUND, game);
				else if (game->map[x][y] == ' ')
					put_case(x, y, GROUND, game);
				else if (game->map[x][y] == '2')
					put_case(x, y, SPRITE, game);
				y++;
			}
			x++;
		}
		print_minimap2(game);
	}
}

void	print_minimap2(t_game *game)
{
	put_player_case(PLAYER, game);
	mlx_put_image_to_window(game->data.mlx_ptr,
		game->data.mlx_win, game->data.img, 0, 0);
}

void	put_case(int x, int y, int color, t_game *game)
{
	int	x_p;
	int	y_p;
	int	x_ref;
	int	y_ref;

	x_ref = x * SIZE;
	y_ref = y * SIZE;
	x_p = x * SIZE;
	while (x_p < x_ref + SIZE)
	{
		y_p = y * SIZE;
		while (y_p < y_ref + SIZE)
			my_mlx_pixel_put(&game->data, x_p, y_p++, color);
		x_p++;
	}
}

void	put_player_case(int color, t_game *game)
{
	int	x_p;
	int	y_p;

	x_p = (game->ray.posx * SIZE) - 4;
	while (x_p < (game->ray.posx * SIZE) + 4)
	{
		y_p = (game->ray.posy * SIZE) - 4;
		while (y_p < (game->ray.posy * SIZE) + 4)
			my_mlx_pixel_put(&game->data, x_p, y_p++, color);
		x_p++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = (char *)data->addr + (x * data->line_length
			+ y * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
