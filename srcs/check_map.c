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
	game->player.posx = x;
	game->player.posy = y;
	printf("%d\n", game->player.dir);
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
			if (map[y][x] == 'E' || map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'W')
				if (check_dir(x, y, map[y][x], game))
					return (2);
			x++;
		}
		y++;
	}
	return (0);
}


int	check_pos(t_game *game, char **map, int x, int y)
{
	if (x == 0 || y == 0 || x == game->map.len_max - 1 || y == game->map.max_y - 1)
		return (1);
	if (map[y][x - 1] == ' ' || map[y][x + 1] == ' ' || map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
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
			if (map[y][x] == '0' || map[y][x] == 'W' || map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E')
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

int	check_map(t_game *game)
{
	char	**map;
	int		x;

	map = game->map.map;
	if (check_close(game, map))
	{
		printf("error\nThe map isnt close\n");
		return (1);
	}
	x = check_char(game, map);
	if (x == 1)
	{
		printf("error\nInvalid map forbidden carractere detected\n");
		return (1);
	}
	else if (x == 2)
	{
		printf("error\nTo many players detected in the map\n");
		return (1);
	}
	if (game->player.dir == -17)
	{
		printf("error\nNo player detected\n");
		return(1);
	}
	if (check_textures(game))
	{
		printf("invalid textures\n");
		return (1);
	}
	return (0);
}
