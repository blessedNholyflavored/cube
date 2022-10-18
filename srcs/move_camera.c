/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:10:35 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/10/18 15:10:37 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_cam_right(t_game *game)
{
	double	rot_speed;
	double	olddirx;
	double	oldplanex;

	oldplanex = game->player.planex;
	rot_speed = (10.0 / 1000.0) * 3.0;
	olddirx = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(rot_speed)
		- game->player.diry * sin(rot_speed);
	game->player.diry = olddirx * sin(rot_speed)
		+ game->player.diry * cos(rot_speed);
	game->player.planex = game->player.planex * cos(rot_speed)
		- game->player.planey * sin(rot_speed);
	game->player.planey = oldplanex * sin(rot_speed)
		+ game->player.planey * cos(rot_speed);
}

void	move_cam_left(t_game *game)
{
	double	rot_speed;
	double	olddirx;
	double	oldplanex;

	oldplanex = game->player.planex;
	rot_speed = 0.03;
	olddirx = game->player.dirx;
	game->player.dirx = game->player.dirx * cos(-rot_speed)
		- game->player.diry * sin(-rot_speed);
	game->player.diry = olddirx * sin(-rot_speed)
		+ game->player.diry * cos(-rot_speed);
	game->player.planex = game->player.planex * cos(-rot_speed)
		- game->player.planey * sin(-rot_speed);
	game->player.planey = oldplanex * sin(-rot_speed)
		+ game->player.planey * cos(-rot_speed);
}

int	key_codes(int keycode, t_game *game)
{
	if (keycode == 97)
		move_left(game);
	if (keycode == 100)
		move_right(game);
	if (keycode == 119)
		move_ahead(game);
	if (keycode == 115)
		move_back(game);
	if (keycode == 65361)
		move_cam_left(game);
	if (keycode == 65363)
		move_cam_right(game);
	if (keycode == 65307)
		ft_close(game);
	return (1);
}

int	ft_keys(t_game *game)
{
	free(game->window.mlx);
	exit(0);
	return (0);
}
