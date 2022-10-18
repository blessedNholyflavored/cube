/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:18:50 by Mmhaya            #+#    #+#             */
/*   Updated: 2022/10/18 15:31:22 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_ahead(t_game *game)
{
	int		y;
	int		x;
	double	move_speed;

	move_speed = 0.05;
	x = game->player.posx;
	y = (int)(game->player.posy + game->player.diry * move_speed);
	if (game->map.map[y][x] != '1')
		game->player.posy += game->player.diry * move_speed;
	x = (int)(game->player.posx + game->player.dirx * move_speed);
	y = game->player.posy;
	if (game->map.map[y][x] != '1')
		game->player.posx += game->player.dirx * move_speed;
}

void	move_back(t_game *game)
{
	int		y;
	int		x;
	double	move_speed;

	move_speed = 0.05;
	x = game->player.posx;
	y = (int)(game->player.posy - game->player.diry * move_speed);
	if (game->map.map[y][x] != '1')
		game->player.posy -= game->player.diry * move_speed;
	x = (int)(game->player.posx - game->player.dirx * move_speed);
	y = game->player.posy;
	if (game->map.map[y][x] != '1')
		game->player.posx -= game->player.dirx * move_speed;
}

void	move_left(t_game *game)
{
	int		y;
	int		x;
	double	move_speed;

	move_speed = 0.05;
	x = game->player.posx;
	y = (int)(game->player.posy - game->player.planey * move_speed);
	if (game->map.map[y][x] != '1')
		game->player.posy -= game->player.planey * move_speed;
	x = (int)(game->player.posx - game->player.planex * move_speed);
	y = game->player.posy;
	if (game->map.map[y][x] != '1')
		game->player.posx -= game->player.planex * move_speed;
}

void	move_right(t_game *game)
{
	int		y;
	int		x;
	double	move_speed;

	move_speed = 0.05;
	x = game->player.posx;
	y = (int)(game->player.posy + game->player.planey * move_speed);
	if (game->map.map[y][x] != '1')
		game->player.posy += game->player.planey * move_speed;
	x = (int)(game->player.posx + game->player.planex * move_speed);
	y = game->player.posy;
	if (game->map.map[y][x] != '1')
		game->player.posx += game->player.planex * move_speed;
}
