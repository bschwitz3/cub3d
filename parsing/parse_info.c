/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 11:39:05 by bschwitz          #+#    #+#             */
/*   Updated: 2023/05/08 15:46:17 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_color_resolution(char **str, t_game *game)
{
	int			i;

	i = 0;
	game->i = 1;
	if (game->sizeline > 0 && (game->no == NULL || game->so == NULL
			|| game->we == NULL || game->ea == NULL || game->s == NULL))
	{
		return ;
		ft_error(game, "Map before elements or miss elements\n");
	}
	game->rx = RESX;
	game->ry = RESY;
	if (*str[i] == 'F')
		game->f = create_rgb(ft_atoi_f(*str, game));
	else if (*str[i] == 'C')
		game->c = create_rgb(ft_atoi_c(*str, game));
}

int	create_rgb(int	*color)
{
	int	res;

	res = ((color[0] & 0xff) << 16) + ((color[1] & 0xff) << 8)
		+ (color[2] & 0xff);
	return (res);
}

void	ft_texture(char *str, t_game *game)
{
	int			i;

	i = 0;
	if (str[i] == 'N' && str[i + 1] == 'O')
		ft_path_texture(str, &game->no, game, 2);
	else if (str[i] == 'S' && str[i + 1] == 'O')
		ft_path_texture(str, &game->so, game, 2);
	else if (str[i] == 'W' && str[i + 1] == 'E')
		ft_path_texture(str, &game->we, game, 2);
	else if (str[i] == 'E' && str[i + 1] == 'A')
		ft_path_texture(str, &game->ea, game, 2);
	else if (str[i] == 'S' && str[i + 1] != 'O')
		ft_path_texture(str, &game->s, game, 1);
	else if (str[0] != 'N' && str[0] != 'S' && str[0] != 'W' && str[0] != 'E'
		&& str[0] != 'R' && str[0] != 'F' && str[0] != 'C'
		&& str[0] > 65 && str[0] < 122)
		ft_error(game \
				, "First char of an element isn't an identifiant\n");
}

int	ft_path_texture(char *str, char **texture, t_game *game, int j)
{
	int		i;

	i = 0;
	if (ft_charinstr(str, '.') == 0 || ft_charinstr(str, '/') == 0
		|| ft_strlen2(str) <= 2)
		ft_error(game, "Texture path is invalid\n");
	while (str[j] != '.')
	{
		if (str[j] != ' ' && str[j] != '.')
			ft_error(game, "Identifiant or path texture is invalid");
		j++;
	}
	*texture = (char *)(malloc(sizeof(char) * (ft_strlen2(str) + 1)));
	if (!*texture)
		ft_error(game, "Malloc texture texture in parsing failed\n");
	while (str[j] != '\0')
	{
		(*texture)[i] = str[j];
		i++;
		j++;
	}
	(*texture)[i] = '\0';
	return (0);
}
