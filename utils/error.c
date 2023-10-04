/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:07:59 by bschwitz          #+#    #+#             */
/*   Updated: 2023/05/08 14:18:05 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error_start(char *str)
{
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
}

void	ft_error(t_game *game, char *str)
{
	int	i;

	i = -1;
	write(1, "Error\n", 6);
	write(1, str, ft_strlen(str));
	if (game->no)
		free(game->no);
	if (game->so)
		free(game->so);
	if (game->we)
		free(game->we);
	if (game->ea)
		free(game->ea);
	if (game->s)
		free(game->s);
	if (game->map)
	{
		while (++i < game->nbline)
			free(game->map[i]);
	}
	if (game->map)
		free(game->map);
	ft_error2(game);
}

void	ft_error2(t_game *game)
{
	int	i;

	i = -1;
	if (game->check)
	{
		while (++i < game->nbline)
			free(game->check[i]);
	}
	if (game->check)
		free(game->check);
	if (game->sp.order)
		free(game->sp.order);
	if (game->sp.dist)
		free(game->sp.dist);
	ft_exit(game);
}
// system("leaks Cub3D");

int	ft_exit(t_game *game)
{
	game->dx = 0;
	if (game->data.img)
		mlx_destroy_image(game->data.mlx_ptr, game->data.img);
	if (game->texture[0].img)
		mlx_destroy_image(game->data.mlx_ptr, game->texture[0].img);
	if (game->texture[1].img)
		mlx_destroy_image(game->data.mlx_ptr, game->texture[1].img);
	if (game->texture[2].img)
		mlx_destroy_image(game->data.mlx_ptr, game->texture[2].img);
	if (game->texture[3].img)
		mlx_destroy_image(game->data.mlx_ptr, game->texture[3].img);
	if (game->texture[4].img)
		mlx_destroy_image(game->data.mlx_ptr, game->texture[4].img);
	if (game->data.mlx_win)
		mlx_destroy_window(game->data.mlx_ptr, game->data.mlx_win);
	exit(0);
}

void	ft_verify_errors(t_game *game)
{
	if (game->depart == 'x')
		ft_error(game, "No player\n");
}
