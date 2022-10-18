/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mmhaya <Mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:18:50 by Mmhaya            #+#    #+#             */
/*   Updated: 2022/10/17 00:16:18 by Mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_cam_right(t_game *game)
{
	double	rot_speed = (10.0 / 1000.0) * 3.0; 
	double oldDirX = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(rot_speed) - game->player.diry * sin(rot_speed);
	game->player.diry = oldDirX * sin(rot_speed) + game->player.diry * cos(rot_speed);
	double oldPlaneX = game->player.planex;
	game->player.planex = game->player.planex * cos(rot_speed) - game->player.planey * sin(rot_speed);
	game->player.planey = oldPlaneX * sin(rot_speed) + game->player.planey * cos(rot_speed);
}

void	move_cam_left(t_game *game)
{
	double	rot_speed = 0.03; 
	double oldDirX = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(-rot_speed) - game->player.diry * sin(-rot_speed);
	game->player.diry = oldDirX * sin(-rot_speed) + game->player.diry * cos(-rot_speed);
	double oldPlaneX = game->player.planex;
	game->player.planex = game->player.planex * cos(-rot_speed) - game->player.planey * sin(-rot_speed);
	game->player.planey = oldPlaneX * sin(-rot_speed) + game->player.planey * cos(-rot_speed);
}

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
	int	y;
	int	x;
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
	int	y;
	int	x;
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
	int	y;
	int	x;
	double	move_speed;

	move_speed = 0.05;
	x = game->player.posx;
	y = (int)(game->player.posy + game->player.planey * move_speed);
	game->player.posx += game->player.planex * move_speed;
	x = (int)(game->player.posy + game->player.planey * move_speed);
	y = game->player.posy;
	game->player.posy += game->player.planey * move_speed;
}
