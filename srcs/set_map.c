/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mmhaya <Mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:46:39 by mmhaya            #+#    #+#             */
/*   Updated: 2022/10/19 00:15:00 by Mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	init_map(t_game *game, int y)
{
	char	**file;

	file = game->map.file;
	y = find_map(file, y);
	if (y == 1)
		return (1);
	if (set_map(game, file, y))
		return (1);
	if (check_map(game))
		return (1);
	return (0);
}

int	max_len(t_game *game, char **file, int x)
{
	int	y;
	int	len_max;

	len_max = 0;
	while (file[x])
	{
		y = 0;
		while (file[x][y])
		{
			y++;
		}
		if (y > len_max)
			len_max = y;
		x++;
	}
	game->map.len_max = len_max;
	return (len_max);
}

int	set_map(t_game *game, char **file, int y)
{
	int	x;
	int	i;

	i = 0;
	x = y;
	while (file[x])
		x++;
	x = x - y;
	game->map.max_y = x;
	game->map.map = malloc(sizeof(char *) * (x + 1));
	if (!game->map.map)
		return (1);
	x = y;
	y = max_len(game, file, x);
	while (file[x])
	{
		game->map.map[i] = malloc(sizeof(char) * (y + 1));
		if (!game->map.map[i])
			return (1);
		copy_map(game, file, i, x);
		i++;
		x++;
	}
	game->map.map[i] = NULL;
	return (0);
}

void	copy_map(t_game *game, char **file, int i, int x)
{
	int	y;
	int	len_max;

	len_max = game->map.len_max;
	y = 0;
	while (file[x][y])
	{
		game->map.map[i][y] = file[x][y];
		y++;
	}
	while (y < len_max)
	{
		game->map.map[i][y] = ' ';
		y++;
	}
	game->map.map[i][y] = '\0';
}

int	find_map(char **file, int y)
{
	int		x;

	x = 0;
	while (file[y])
	{
		while (file[y][x])
		{
			if (file[y][x] != ' ')
			{
				if (file[y][x] != '1')
					return (1);
				else
					return (y);
			}
			x++;
		}
		y++;
	}
	return (1);
}
