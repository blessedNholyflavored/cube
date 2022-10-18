/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:27:05 by mmhaya            #+#    #+#             */
/*   Updated: 2022/07/04 19:30:01 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_pos(t_game *game, char **map, int x, int y)
{
	if (x == 0 || y == 0 || x == game->map.len_max - 1
		|| y == game->map.max_y - 1)
		return (1);
	if (map[y][x - 1] == ' ' || map[y][x + 1] == ' '
		|| map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
		return (1);
	return (0);
}

int	check_close(t_game *game, char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'W' || map[y][x] == 'N'
				|| map[y][x] == 'S' || map[y][x] == 'E')
				if (check_pos(game, map, x, y))
					return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	check_textures(t_game *game)
{
	if (game->setup.floor.red < 0 || game->setup.floor.red > 255)
		return (1);
	if (game->setup.floor.green < 0 || game->setup.floor.green > 255)
		return (1);
	if (game->setup.floor.blue < 0 || game->setup.floor.blue > 255)
		return (1);
	if (game->setup.ceiling.red < 0 || game->setup.ceiling.red > 255)
		return (1);
	if (game->setup.ceiling.green < 0 || game->setup.ceiling.green > 255)
		return (1);
	if (game->setup.ceiling.blue < 0 || game->setup.ceiling.blue > 255)
		return (1);
	return (0);
}

int	ft_error(int i)
{
	if (i == 1)
	{
		printf("error\nThe map isnt close\n");
		exit(0);
	}
	else if (i == 2)
	{
		printf("error\nInvalid map forbidden carractere detected\n");
		exit(0);
	}
	else if (i == 3)
	{
		printf("error\nTo many players detected in the map\n");
		exit(0);
	}
	return (0);
}

int	check_map(t_game *game)
{
	char	**map;
	int		x;

	map = game->map.map;
	if (check_close(game, map))
		ft_error(1);
	x = check_char(game, map);
	if (x == 1)
		ft_error(2);
	else if (x == 2)
		ft_error(3);
	if (game->player.dir == -17)
	{
		printf("error\nNo player detected\n");
		return (1);
	}
	if (check_textures(game))
	{
		printf("invalid textures\n");
		return (1);
	}
	return (0);
}
