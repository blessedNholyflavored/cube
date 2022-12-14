/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:45:20 by mmhaya            #+#    #+#             */
/*   Updated: 2022/10/19 19:08:21 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_struct(t_game *game)
{
	game->player.dir = -17;
	game->check.n = 0;
	game->check.s = 0;
	game->check.w = 0;
	game->check.e = 0;
	game->check.f = 0;
	game->check.c = 0;
	game->setup.path_so = NULL;
	game->setup.path_no = NULL;
	game->setup.path_we = NULL;
	game->setup.path_ea = NULL;
	game->map.x = 0;
	game->map.y = 0;
	game->map.fd = -17;
	game->map.file = NULL;
	game->map.map = NULL;
}

int	parsing_map(t_game *game, int ac, char **av)
{
	int	y;

	if (ac != 2)
	{
		printf("error\nWrong number of arguments\n");
		return (1);
	}
	init_struct_image(game);
	init_struct(game);
	y = check_arg(game, av[1]);
	if (y == 1)
		return (2);
	if (init_map(game, y))
		return (3);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (parsing_map(&game, ac, av))
		return (1);
	if (init_window(&game))
		return (1);
	return (0);
}
