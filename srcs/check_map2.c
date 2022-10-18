/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:55:50 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/10/18 16:55:51 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_dir(double x, double y, char c, t_game *game)
{
	if (game->player.dir != -17)
	{
		return (1);
	}
	if (c == 'N')
		game->player.dir = NORTH;
	else if (c == 'S')
		game->player.dir = SOUTH;
	else if (c == 'E')
		game->player.dir = EAST;
	else if (c == 'W')
		game->player.dir = WEST;
	game->player.posx = x + 0.5;
	game->player.posy = y + 0.5;
	return (0);
}

int	check_char(t_game *game, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != ' ' && map[y][x] != 'N' && map[y][x] != 'S'
					&& map[y][x] != 'E' && map[y][x] != 'W' && map[y][x] != '1'
					&& map[y][x] != '0')
				return (1);
			if (map[y][x] == 'E' || map[y][x] == 'N'
				|| map[y][x] == 'S' || map[y][x] == 'W')
				if (check_dir(x, y, map[y][x], game))
					return (2);
			x++;
		}
		y++;
	}
	return (0);
}