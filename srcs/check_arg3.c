/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mmhaya <Mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:23:38 by Mmhaya            #+#    #+#             */
/*   Updated: 2022/10/19 00:59:28 by Mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_rgb2(t_game *game, char **file, char type, int *x)
{
	if (type == 'f')
	{
		game->setup.floor.red = ft_atoi(file[game->map.tmp] + *x);
		while (file[game->map.tmp][*x] != ',')
			*x += 1;
		*x += 1;
		game->setup.floor.green = ft_atoi(file[game->map.tmp] + *x);
		while (file[game->map.tmp][*x] != ',')
			*x += 1;
		*x += 1;
		game->setup.floor.blue = ft_atoi(file[game->map.tmp] + *x);
	}
	else
	{
		game->setup.ceiling.red = ft_atoi(file[game->map.tmp] + *x);
		while (file[game->map.tmp][*x] != ',')
			*x += 1;
		*x += 1;
		game->setup.ceiling.green = ft_atoi(file[game->map.tmp] + *x);
		while (file[game->map.tmp][*x] != ',')
			*x += 1;
		*x += 1;
		game->setup.ceiling.blue = ft_atoi(file[game->map.tmp] + *x);
	}
}

int	check_rgb(t_game *game, int *i, int y, char type)
{
	char	**file;
	int		x;
	int		nb_virgule;

	nb_virgule = 0;
	x = *i;
	file = game->map.file;
	while (file[y][x])
	{
		if (!(file[y][x] >= '0' && file[y][x] <= '9') && file[y][x] != ','
			&& file[y][x] != ' ')
			return (1);
		if (file[y][x] == ',')
			nb_virgule += 1;
		x++;
	}
	if (nb_virgule != 2)
		return (1);
	x = *i;
	game->map.tmp = y;
	check_rgb2(game, file, type, &x);
	while (file[y][x])
		x++;
	*i = x;
	return (0);
}

int	check_setup2(t_game *game, char **file, int *x, int y)
{
	if (file[y][*x] != ' ')
	{
		if (find_arg(game, file, x, y))
			return (1);
	}
	else
	{
		while (file[y][*x])
		{
			if (file[y][*x] != ' ')
				return (1);
			*x += 1;
		}
	}
	return (0);
}

int	check_setup(t_game *game)
{
	char	**file;
	int		x;
	int		y;

	y = 0;
	file = game->map.file;
	while (file[y])
	{
		x = 0;
		while (file[y][x])
		{
			if (check_setup2(game, file, &x, y))
				return (1);
			if (!file[y][x])
				break ;
			x++;
		}
		if (!final_check(game))
			break ;
		y++;
	}
	return (y + 1);
}
