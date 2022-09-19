/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:26:16 by mmhaya            #+#    #+#             */
/*   Updated: 2022/07/07 10:51:20 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_no(t_game *game, char **file, int *x, int y)
{
	int	i;
	int	j;

	i = *x;
	j = 0;
	if (file[y][i + 1] != 'O')
		return (1);
	i += 2;
	while (file[y][i] == ' ')
		i++;
	if (file[y][i] != '.' || file[y][i + 1] != '/')
		return (1);
	game->setup.path_no = malloc(ft_strlen_space(file[y] + i) + 1);
	if (!game->setup.path_no)
		return (1);
	while (file[y][i] && file[y][i] != ' ')
	{
		game->setup.path_no[j] = file[y][i];
		i++;
		j++;
	}
	game->setup.path_no[j] = '\0';
	game->check.n += 1;
	*x = i;
	return (0);
}

int	check_so(t_game *game, char **file, int *x, int y)
{
	int	i;
	int	j;

	i = *x;
	j = 0;
	if (file[y][i + 1] != 'O')
		return (1);
	i += 2;
	while (file[y][i] == ' ')
		i++;
	if (file[y][i] != '.' || file[y][i + 1] != '/')
		return (1);
	game->setup.path_so = malloc(ft_strlen_space(file[y] + i) + 1);
	if (!game->setup.path_so)
		return (1);
	while (file[y][i] && file[y][i] != ' ')
	{
		game->setup.path_so[j] = file[y][i];
		i++;
		j++;
	}
	game->setup.path_so[j] = '\0';
	game->check.s += 1;
	*x = i;
	return (0);
}

int	find_arg(t_game *game, char **file, int *x, int y)
{
	int	i;

	i = 0;
	if (file[y][*x] != 'N' && file[y][*x] != 'S' && file[y][*x] != 'W'
			&& file[y][*x] != 'E' && file[y][*x] != 'F' && file[y][*x] != 'C')
		return (1);
	if (file[y][*x] == 'N')
		i = check_no(game, file, x, y);
	else if (file[y][*x] == 'S')
		i = check_so(game, file, x, y);
	else if (file[y][*x] == 'W')
		i = check_we(game, file, x, y);
	else if (file[y][*x] == 'E')
		i = check_ea(game, file, x, y);
	else if (file[y][*x] == 'F')
		i = check_fl(game, file, x, y);
	else if (file[y][*x] == 'C')
		i = check_ce(game, file, x, y);
	if (i != 0)
		return (1);
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
			if (file[y][x] != ' ')
			{
				if (find_arg(game, file, &x, y))
					return (1);
			}
				else
					while (file[y][x])
					{
						if (file[y][x] != ' ')
							return (1);
						x++;
					}
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

	int	check_arg(t_game *game, char *av)
{
	int	size;
	int	y;

	size = ft_strlen(av);
	if (size <= 4)
		return (1);
	if (av[size - 4] == '/')
		return (1);
	if (ft_strcmp(&av[size - 4], ".cub"))
		return (1);
	game->map.fd = open(av, O_RDONLY);
	if (game->map.fd < 0 || read(game->map.fd, 0, 0) == -1)
		return (1);
	game->map.file = ft_get_file(game->map.fd, 0);
	if (!game->map.file)
		return (1);
	y = check_setup(game);
	if (y == 1)
		return (1);
	if (final_check(game))
		return (1);
	return (y);
}
