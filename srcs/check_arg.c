/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:24:40 by mmhaya            #+#    #+#             */
/*   Updated: 2022/10/18 15:02:54 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_rgb(t_game *game, int *i, int y, char type)
{
	char	**file;
	int		x;
	int		nb_virgule;

	nb_virgule = 0;
	x = *i;
	file = game->map.file;
	while (file[y][x] && file[y][x] != ' ')
	{
		if (!(file[y][x] >= '0' && file[y][x] <= '9') && file[y][x] != ',')
			return (1);
		if (file[y][x] == ',')
			nb_virgule += 1;
		x++;
	}
	if (nb_virgule != 2)
		return (1);
	x = *i;
	if (type == 'f')
	{
		game->setup.floor.red = ft_atoi(file[y] + x);
		while (file[y][x] != ',')
			x++;
		x++;
		game->setup.floor.green = ft_atoi(file[y] + x);
		while (file[y][x] != ',')
			x++;
		x++;
		game->setup.floor.blue = ft_atoi(file[y] + x);
	}
	else
	{
		game->setup.ceiling.red = ft_atoi(file[y] + x);
		while (file[y][x] != ',')
			x++;
		x++;
		game->setup.ceiling.green = ft_atoi(file[y] + x);
		while (file[y][x] != ',')
			x++;
		x++;
		game->setup.ceiling.blue = ft_atoi(file[y] + x);
	}
	while (file[y][x] != ' ' && file[y][x])
		x++;
	*i = x;
	return (0);
}

int	check_ce(t_game *game, char **file, int *x, int y)
{
	int	i;

	i = *x;
	if (file[y][i + 1] != ' ')
		return (1);
	i += 1;
	while (file[y][i] == ' ')
		i++;
	if (check_rgb(game, &i, y, 'c'))
		return (1);
	game->check.c += 1;
	*x = i;
	return (0);
}

int	check_fl(t_game *game, char **file, int *x, int y)
{
	int	i;

	i = *x;
	if (file[y][i + 1] != ' ')
		return (1);
	i += 1;
	while (file[y][i] == ' ')
		i++;
	if (check_rgb(game, &i, y, 'f'))
		return (1);
	game->check.f += 1;
	*x = i;
	return (0);
}

int	check_ea(t_game *game, char **file, int *x, int y)
{
	int	i;
	int	j;

	i = *x;
	j = 0;
	if (file[y][i + 1] != 'A')
		return (1);
	i += 2;
	while (file[y][i] == ' ')
		i++;
	if (file[y][i] != '.' || file[y][i + 1] != '/')
		return (1);
	game->setup.path_ea = malloc(ft_strlen_space(file[y] + i) + 1);
	if (!game->setup.path_ea)
		return (1);
	while (file[y][i] && file[y][i] != ' ')
	{
		game->setup.path_ea[j] = file[y][i];
		i++;
		j++;
	}
	game->setup.path_ea[j] = '\0';
	game->check.e += 1;
	*x = i;
	return (0);
}

int	check_we(t_game *game, char **file, int *x, int y)
{
	int	i;
	int	j;

	i = *x;
	j = 0;
	if (file[y][i + 1] != 'E')
		return (1);
	i += 2;
	while (file[y][i] == ' ')
		i++;
	if (file[y][i] != '.' || file[y][i + 1] != '/')
		return (1);
	game->setup.path_we = malloc(ft_strlen_space(file[y] + i) + 1);
	if (!game->setup.path_we)
		return (1);
	while (file[y][i] && file[y][i] != ' ')
	{
		game->setup.path_we[j] = file[y][i];
		i++;
		j++;
	}
	game->setup.path_we[j] = '\0';
	game->check.w += 1;
	*x = i;
	return (0);
}
