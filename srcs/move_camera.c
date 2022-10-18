/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mmhaya <Mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:10:35 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/10/18 23:48:31 by Mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	move_cam_right(t_game *game)
{
	double	rot_speed;
	double	olddirx;
	double	oldplanex;

	oldplanex = game->player.planex;
	rot_speed = 0.04;
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
	rot_speed = 0.04;
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

void	free_tab(char **tab)
{
	int	y;

	y = 0;
	while (tab[y])
	{
		free(tab[y]);
		y++;
	}
	free(tab);
}

void	free_all(t_game *game)
{
	free_tab(game->map.file);
	free_tab(game->map.map);
	free(game->setup.path_no);
	free(game->setup.path_ea);
	free(game->setup.path_so);
	free(game->setup.path_we);
	close(game->map.fd);
}

int	ft_exit(t_game *game)
{
	if (game->assets.ea.img)
		mlx_destroy_image(game->window.mlx, game->assets.ea.img);
	if (game->assets.we.img)
		mlx_destroy_image(game->window.mlx, game->assets.we.img);
	if (game->assets.no.img)
		mlx_destroy_image(game->window.mlx, game->assets.no.img);
	if (game->assets.so.img)
		mlx_destroy_image(game->window.mlx, game->assets.so.img);
	if (game->img.img)
		mlx_destroy_image(game->window.mlx, game->img.img);
	if (game->window.mlx_win)
		mlx_destroy_window(game->window.mlx, game->window.mlx_win);
	if (game->window.mlx)
	{
		mlx_destroy_display(game->window.mlx);
		free(game->window.mlx);
	}
	free_all(game);
	exit(0);
	return (0);
}
