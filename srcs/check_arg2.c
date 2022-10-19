/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mmhaya <Mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 14:26:16 by mmhaya            #+#    #+#             */
/*   Updated: 2022/10/19 01:00:45 by Mmhaya           ###   ########.fr       */
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
	{
		printf("Error\nWrong rgb format\n");
		ft_exit(game);
	}
	return (0);
}

int	ft_error2(t_game *game, int i)
{
	if (i == 1)
	{
		printf("error\nnot enough arguments\n");
		exit(0);
	}
	else if (i == 2)
	{
		printf("error\ncheck your arguments\n");
		exit(0);
	}
	else if (i == 3)
	{
		printf("error\ndont trick the .cub rule\n");
		exit(0);
	}
	else if (i == 4)
	{
		printf("cant open the file\n");
		ft_exit(game);
	}
	return (0);
}

int	ft_error3(t_game *game, int i)
{
	if (i == 1)
	{
		printf("error\ncan't get the file\n");
		ft_exit(game);
	}
	else if (i == 2)
	{
		printf("error\nsomething is wrong in your map settings\n");
		ft_exit(game);
	}
	return (0);
}

int	check_arg(t_game *game, char *av)
{
	int	size;
	int	y;

	size = ft_strlen(av);
	if (size <= 4)
		ft_error2(game, 1);
	if (av[size - 5] == '/')
		ft_error2(game, 2);
	if (ft_strcmp(&av[size - 4], ".cub"))
		ft_error2(game, 3);
	game->map.fd = open(av, O_RDONLY);
	if (game->map.fd < 0 || read(game->map.fd, 0, 0) == -1)
		ft_error2(game, 4);
	game->map.file = ft_get_file(game->map.fd, 0);
	if (!game->map.file)
		ft_error3(game, 1);
	y = check_setup(game);
	if (y == 1)
		ft_error3(game, 2);
	if (final_check(game))
		ft_error3(game, 2);
	return (y);
}
