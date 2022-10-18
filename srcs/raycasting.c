/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:57:18 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/10/18 15:16:30 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	go_chercher_la_distance_du_rayon_mec(t_game *game)
{
	if (!game->ray.side)
	{
		game->ray.perpalldist = (game->ray.sidex - game->ray.deltax);
		game->ray.wallx = game->player.posy + game->ray.perpalldist
			* game->ray.diry;
	}
	else
	{
		game->ray.perpalldist = (game->ray.sidey - game->ray.deltay);
		game->ray.wallx = game->player.posx + game->ray.perpalldist
			* game->ray.dirx;
	}
	if (game->ray.side == 0 && game->ray.dirx > 0)
		game->ray.sidewall = EAST;
	else if (game->ray.side == 0 && game->ray.dirx <= 0)
		game->ray.sidewall = WEST;
	else if (game->ray.side == 1 && game->ray.diry > 0)
		game->ray.sidewall = SOUTH;
	else
		game->ray.sidewall = NORTH;
}

void	go_chercher_les_murs(t_game *game)
{
	int	wall;

	wall = 0;
	while (!wall)
	{
		if (game->ray.sidex < game->ray.sidey)
		{
			game->ray.sidex += game->ray.deltax;
			game->ray.mapx += game->ray.stepx;
			game->ray.side = 0;
		}
		else
		{
			game->ray.sidey += game->ray.deltay;
			game->ray.mapy += game->ray.stepy;
			game->ray.side = 1;
		}
		if (game->map.map[game->ray.mapy][game->ray.mapx] == '1')
		{
			wall = 1;
		}
	}
}

void	verification_ray(t_game *game)
{
	if (game->ray.dirx < 0)
	{
		game->ray.stepx = -1;
		game->ray.sidex = (game->player.posx - game->ray.mapx)
			* game->ray.deltax;
	}
	else
	{
		game->ray.stepx = 1;
		game->ray.sidex = (game->ray.mapx + 1 - game->player.posx)
			* game->ray.deltax;
	}
	if (game->ray.diry < 0)
	{
		game->ray.stepy = -1;
		game->ray.sidey = (game->player.posy - game->ray.mapy)
			* game->ray.deltay;
	}
	else
	{
		game->ray.stepy = 1;
		game->ray.sidey = (game->ray.mapy + 1 - game->player.posy)
			* game->ray.deltay;
	}
}

int	init_ray(t_game *game, int col)
{
	game->ray.camerax = 2 * col / (double)WIDTH - 1;
	game->ray.dirx = game->player.dirx + game->player.planex
		* game->ray.camerax;
	game->ray.diry = game->player.diry + game->player.planey
		* game->ray.camerax;
	game->ray.deltax = fabs(1 / game->ray.dirx);
	game->ray.deltay = fabs(1 / game->ray.diry);
	game->ray.mapx = game->player.posx;
	game->ray.mapy = game->player.posy;
	return (0);
}

int	raycasting(t_game *game)
{
	int	col;
	int	px;

	col = 0;
	draw_sky_floor_colors(game);
	while (col < WIDTH)
	{
		init_ray(game, col);
		verification_ray(game);
		go_chercher_les_murs(game);
		go_chercher_la_distance_du_rayon_mec(game);
		texture_colonne(game);
		game->ray.wallx -= floor(game->ray.wallx);
		px = game->ray.firstpixel;
		while (px < game->ray.lastpixel)
			wall_pixel_put(game, col, px++);
		col++;
	}
	mlx_put_image_to_window(game->window.mlx, game->window.mlx_win,
		game->img.img, 0, 0);
	return (0);
}
