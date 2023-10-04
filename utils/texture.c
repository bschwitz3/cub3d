/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:12:53 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/25 12:25:43 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_get_texture(t_game *game)
{
	game->texture[0].img = mlx_xpm_file_to_image(game->data.mlx_ptr,
			game->no, &(game->texture[0].width),
			&(game->texture[0].height));
	if (!game->texture[0].img)
	{
		write(1, "No textures for NO, default set.\n", 34);
		ft_path_texture("./textures/default.xpm", &game->no, game, 0);
		game->texture[0].img = mlx_xpm_file_to_image(game->data.mlx_ptr,
				game->no, &(game->texture[0].width),
				&(game->texture[0].height));
	}
	game->texture[1].img = mlx_xpm_file_to_image(game->data.mlx_ptr,
			game->so, &(game->texture[1].width),
			&(game->texture[1].height));
	if (!game->texture[1].img)
	{
		write(1, "No textures for SO, default set.\n", 34);
		ft_path_texture("./textures/default.xpm", &game->so, game, 0);
		game->texture[1].img = mlx_xpm_file_to_image(game->data.mlx_ptr,
				game->so, &(game->texture[1].width),
				&(game->texture[1].height));
	}
	ft_get_texture2(game);
	ft_get_texture_adress(game);
}

void	ft_get_texture_adress(t_game *game)
{
	game->texture[0].addr = (int *)mlx_get_data_addr(game->texture[0].img,
			&game->texture[0].bits_per_pixel,
			&game->texture[0].line_length, &game->texture[0].endian);
	game->texture[1].addr = (int *)mlx_get_data_addr(game->texture[1].img,
			&game->texture[1].bits_per_pixel,
			&game->texture[1].line_length, &game->texture[1].endian);
	game->texture[2].addr = (int *)mlx_get_data_addr(game->texture[2].img,
			&game->texture[2].bits_per_pixel,
			&game->texture[2].line_length, &game->texture[2].endian);
	game->texture[3].addr = (int *)mlx_get_data_addr(game->texture[3].img,
			&game->texture[3].bits_per_pixel,
			&game->texture[3].line_length, &game->texture[3].endian);
	game->texture[4].addr = (int *)mlx_get_data_addr(game->texture[4].img,
			&game->texture[4].bits_per_pixel,
			&game->texture[4].line_length, &game->texture[4].endian);
}

void	ft_draw_texture(t_game *game, int x, int y)
{
	y = game->ray.drawstart - 1;
	ft_init_texture(game);
	game->t.step = 1.0 * game->texture[0].height / game->ray.lineheight;
	game->t.texx = (int)(game->t.wallx * (double)game->texture
		[game->t.texdir].width);
	if (game->ray.side == 0 && game->ray.raydirx > 0)
		game->t.texx = game->texture[game->t.texdir].width
			- game->t.texx - 1;
	if (game->ray.side == 1 && game->ray.raydiry < 0)
		game->t.texx = game->texture[game->t.texdir].width
			- game->t.texx - 1;
	game->t.texpos = (game->ray.drawstart - game->ry / 2
			+ game->ray.lineheight / 2) * game->t.step;
	while (++y <= game->ray.drawend)
	{
		game->t.texy = (int)game->t.texpos
			& (game->texture[game->t.texdir].height - 1);
		game->t.texpos += game->t.step;
		if (y < game->ry && x < game->rx)
			game->data.addr[y * game->data.line_length / 4 + x]
				= game->texture[game->t.texdir].addr[game->t.texy
				* game->texture[game->t.texdir].line_length / 4 + game->t.texx];
	}
}

void	ft_init_texture(t_game *game)
{
	if (game->ray.side == 0 && game->ray.raydirx < 0)
		game->t.texdir = 0;
	if (game->ray.side == 0 && game->ray.raydirx >= 0)
		game->t.texdir = 1;
	if (game->ray.side == 1 && game->ray.raydiry < 0)
		game->t.texdir = 2;
	if (game->ray.side == 1 && game->ray.raydiry >= 0)
		game->t.texdir = 3;
	if (game->ray.side == 0)
		game->t.wallx = game->ray.posy + game->ray.perpwalldist \
						* game->ray.raydiry;
	else
		game->t.wallx = game->ray.posx + game->ray.perpwalldist \
						* game->ray.raydirx;
	game->t.wallx -= floor((game->t.wallx));
}
