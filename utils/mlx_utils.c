/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:17:42 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/24 19:38:42 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == FORWARD_W_Z)
		game->data.forward = 1;
	else if (keycode == BACK_S_S)
		game->data.back = 1;
	else if (keycode == LEFT_A_Q)
		game->data.left = 1;
	else if (keycode == RIGHT_D_D)
		game->data.right = 1;
	else if (keycode == ROTATE_LEFT)
		game->data.rotate_left = 1;
	else if (keycode == ROTATE_RIGHT)
		game->data.rotate_right = 1;
	else if (keycode == ESC)
		ft_exit(game);
	else if (keycode == MINIMAP)
		game->data.minimap = 1;
	return (1);
}

int	ft_mouse(int x, int y, t_game *game)
{
	(void) game;
	if (x > 0 && x < (RESX / 2 - RESX / 20) && y < RESY && y > 0)
		game->data.rotate_left = 1;
	else if (x > (RESX / 2 + RESX / 20) && x < RESX && y < RESY && y > 0)
		game->data.rotate_right = 1;
	else
	{
		game->data.rotate_left = 0;
		game->data.rotate_right = 0;
	}
	return (1);
}

int	ft_key_release(int keycode, t_game *game)
{
	if (keycode == FORWARD_W_Z)
		game->data.forward = 0;
	else if (keycode == BACK_S_S)
		game->data.back = 0;
	else if (keycode == LEFT_A_Q)
		game->data.left = 0;
	else if (keycode == RIGHT_D_D)
		game->data.right = 0;
	else if (keycode == ROTATE_LEFT)
		game->data.rotate_left = 0;
	else if (keycode == ROTATE_RIGHT)
		game->data.rotate_right = 0;
	else if (keycode == MINIMAP)
		game->data.minimap = 0;
	return (1);
}
