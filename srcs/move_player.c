/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mmhaya <Mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:18:50 by Mmhaya            #+#    #+#             */
/*   Updated: 2022/10/18 15:04:33 by lkhamlac         ###   ########.fr       */
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
	game->player.posx += game->player.dirx * move_speed;
	x = (int)(game->player.posy + game->player.diry * move_speed);
	y = game->player.posy;
	game->player.posy += game->player.diry * move_speed;
}

void	move_back(t_game *game)
{
	int		y;
	int		x;
	double	move_speed;

	move_speed = 0.05;
	x = game->player.posx;
	y = (int)(game->player.posy - game->player.diry * move_speed);
	game->player.posx -= game->player.dirx * move_speed;
	x = (int)(game->player.posy - game->player.diry * move_speed);
	y = game->player.posy;
	game->player.posy -= game->player.diry * move_speed;
}

void	move_left(t_game *game)
{
	int		y;
	int		x;
	double	move_speed;

	move_speed = 0.05;
	x = game->player.posx;
	y = (int)(game->player.posy - game->player.planey * move_speed);
	game->player.posx -= game->player.planex * move_speed;
	x = (int)(game->player.posy - game->player.planey * move_speed);
	y = game->player.posy;
	game->player.posy -= game->player.planey * move_speed;
}

void	move_right(t_game *game)
{
	int		y;
	int		x;
	double	move_speed;

	move_speed = 0.05;
	x = game->player.posx;
	y = (int)(game->player.posy + game->player.planey * move_speed);
	game->player.posx += game->player.planex * move_speed;
	x = (int)(game->player.posy + game->player.planey * move_speed);
	y = game->player.posy;
	game->player.posy += game->player.planey * move_speed;
}
