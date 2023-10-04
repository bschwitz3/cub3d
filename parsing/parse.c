/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:06:23 by bschwitz          #+#    #+#             */
/*   Updated: 2023/05/08 15:45:37 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_filename(char *str, t_game *game)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
		{
			ft_error_start("Wrong filename\n");
			return (1);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' && str[i + 3] == 'b')
		ft_parsing(str, game);
	else
		ft_error_start("Wrong filename\n");
	return (0);
}

void	ft_parsing(char *fichier, t_game *game)
{
	int		fd;
	int		ret;
	char	*str;

	ret = 1;
	str = NULL;
	ft_init(game);
	fd = open(fichier, O_DIRECTORY);
	if (fd != -1)
		ft_error(game, "Your map file is a directory.");
	fd = open(fichier, O_RDONLY);
	if (fd == -1)
		ft_error(game, "This filename is wrong.");
	ft_parsing2(ret, str, game, fd);
	if (!game->rx || !game->ry)
	{
		game->rx = RES;
		game->ry = RES;
	}
	close(fd);
	if (game->sizeline == 0 || game->nbline == 0)
		ft_error(game, "There is no map\n");
	ft_parsing_map(fichier, game);
}

void	ft_parsing2(int ret, char *str, t_game *game, int fd)
{
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		ft_map(str, game);
		ft_color_resolution(&str, game);
		ft_texture(str, game);
		free(str);
	}
}

int	ft_parsing_map(char *fichier, t_game *game)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	if (!check_map(fichier, game))
		return (1);
	fd = open(fichier, O_RDONLY);
	game->map = malloc(sizeof(char *) * game->nbline);
	if (!game->map)
		return (0);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str);
		if (ft_is_map(str) == 1)
			ft_copy_map(str, game);
		free(str);
	}
	close(fd);
	default_fc(game);
	ft_init_sprite(game);
	ft_mlx(game);
	return (0);
}

int	ft_mlx(t_game *game)
{
	ft_init2(game);
	game->data.mlx_ptr = mlx_init();
	ft_get_texture(game);
	game->data.img = mlx_new_image(game->data.mlx_ptr, game->rx, game->ry);
	game->data.addr = (int *)mlx_get_data_addr(game->data.img,
			&game->data.bits_per_pixel, &game->data.line_length,
			&game->data.endian);
	game->data.mlx_win = mlx_new_window(game->data.mlx_ptr, game->rx,
			game->ry, "Cub3D");
	game->data.img2 = mlx_new_image(game->data.mlx_ptr, game->rx, game->ry);
	game->data.addr2 = (int *)mlx_get_data_addr(game->data.img2,
			&game->data.bits_per_pixel, &game->data.line_length,
			&game->data.endian);
	mlx_hook(game->data.mlx_win, MOUSE, 0, ft_mouse, game);
	mlx_hook(game->data.mlx_win, 2, 1L << 0, ft_key_press, game);
	mlx_hook(game->data.mlx_win, 17, 0, ft_exit, game);
	mlx_loop_hook(game->data.mlx_ptr, ft_raycasting, game);
	mlx_hook(game->data.mlx_win, 3, 1L << 1, ft_key_release, game);
	mlx_loop(game->data.mlx_ptr);
	return (0);
}
