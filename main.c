/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bschwitz <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 10:58:29 by bschwitz          #+#    #+#             */
/*   Updated: 2023/04/25 13:33:27 by bschwitz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac == 2)
		check_filename(av[1], &game);
	else
		write(2, "Error\nWrong number of arguments.\n", 34);
	return (0);
}
