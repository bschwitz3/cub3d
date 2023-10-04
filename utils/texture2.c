/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:16:38 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/25 12:25:59 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_get_texture2(t_game *game)
{
	game->texture[2].img = mlx_xpm_file_to_image(game->data.mlx_ptr,
			game->we, &(game->texture[2].width), &(game->texture[2].height));
	if (!game->texture[2].img)
	{
		write(1, "No textures for WE, default set.\n", 34);
		ft_path_texture("./textures/default.xpm", &game->we, game, 0);
		game->texture[2].img = mlx_xpm_file_to_image(game->data.mlx_ptr,
				game->we, &(game->texture[2].width),
				&(game->texture[2].height));
	}
	game->texture[3].img = mlx_xpm_file_to_image(game->data.mlx_ptr,
			game->ea, &(game->texture[3].width), &(game->texture[3].height));
	if (!game->texture[3].img)
	{
		write(1, "No textures for EA, default set.\n", 34);
		ft_path_texture("./textures/default.xpm", &game->ea, game, 0);
		game->texture[3].img = mlx_xpm_file_to_image(game->data.mlx_ptr,
				game->ea, &(game->texture[3].width),
				&(game->texture[3].height));
	}
	ft_get_texture3(game);
}

void	ft_get_texture3(t_game *game)
{
	game->texture[4].img = mlx_xpm_file_to_image(game->data.mlx_ptr,
			game->s, &(game->texture[4].width), &(game->texture[4].height));
	if (!game->texture[4].img)
	{
		write(1, "No textures for S, default set.\n", 33);
		ft_path_texture("./textures/tonneau.xpm", &game->s, game, 0);
		game->texture[4].img = mlx_xpm_file_to_image(game->data.mlx_ptr,
				game->s, &(game->texture[4].width), &(game->texture[4].height));
	}
}
