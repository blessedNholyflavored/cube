/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mmhaya <Mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:51:35 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/10/18 22:57:01 by Mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_struct_image(t_game *game)
{
	game->assets.we.img = NULL;
	game->assets.we.addr = NULL;
	game->assets.no.img = NULL;
	game->assets.no.addr = NULL;
	game->assets.ea.img = NULL;
	game->assets.ea.addr = NULL;
	game->assets.so.img = NULL;
	game->assets.so.addr = NULL;
	game->img.addr = NULL;
	game->img.img = NULL;
	set_keys(game);
}

void	init_dir2(t_game *game)
{
	if (game->player.dir == EAST)
	{
		game->player.dirx = 1;
		game->player.diry = 0;
		game->player.planex = 0;
		game->player.planey = 0.66;
	}
	else
	{
		game->player.dirx = -1;
		game->player.diry = 0;
		game->player.planex = 0;
		game->player.planey = -0.66;
	}
}

void	init_dir(t_game *game)
{
	if (game->player.dir == NORTH)
	{
		game->player.dirx = 0;
		game->player.diry = -1;
		game->player.planex = 0.66;
		game->player.planey = 0;
	}
	else if (game->player.dir == SOUTH)
	{
		game->player.dirx = 0;
		game->player.diry = 1;
		game->player.planex = -0.66;
		game->player.planey = 0;
	}
	else
		init_dir2(game);
}
