/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:21:28 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/10/18 15:22:36 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
	
t_img	*get_enum(t_game *game)
{
	if (game->ray.sidewall == NORTH)
		return (&(game->assets.no));
	else if (game->ray.sidewall == EAST)
		return (&(game->assets.ea));
	else if (game->ray.sidewall == WEST)
		return (&(game->assets.we));
	else if (game->ray.sidewall == SOUTH)
		return (&(game->assets.so));
	return (0);
}

void	wall_pixel_put(t_game *game, int x, int y)
{
	int		px;
	int		px2;
	int		x2;
	int		y2;
	t_img	*print_wall;

	print_wall = get_enum(game);
	px = game->img.line_length * y + x * game->img.bits_per_pixel / 8;
	y = y - (HEIGHT / 2 - game->ray.line_height / 2);
	x2 = (int)(game->ray.wallx * (double)print_wall->width);
	if (game->ray.sidewall == WEST || game->ray.sidewall == NORTH)
		x2 = print_wall->width - x2 - 1;
	y2 = (int)((double)y * (double)print_wall->height / game->ray.line_height);
	px2 = print_wall->line_length * y2 + x2 * print_wall->bits_per_pixel / 8;
	game->img.addr[px + 2] = (char)print_wall->addr[px2 + 2];
	game->img.addr[px + 1] = (char)print_wall->addr[px2 + 1];
	game->img.addr[px] = (char)print_wall->addr[px2];
}

void	texture_colonne(t_game *game)
{
	t_img	*print_wall;

	print_wall = get_enum(game);
	game->ray.line_height = (int)(HEIGHT / game->ray.perpalldist);
	game->ray.FirstPixel = -game->ray.line_height / 2 + HEIGHT / 2;
	if (game->ray.FirstPixel < 0)
		game->ray.FirstPixel = 0;
	game->ray.PixelLast = game->ray.line_height / 2 + HEIGHT / 2;
	if (game->ray.PixelLast >= HEIGHT)
		game->ray.PixelLast = HEIGHT;
}

int	rgb2int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	draw_sky_floor_colors(t_game *game)
{
	int	x;
	int	y;
	int	sky_color;
	int	floor_color;

	sky_color = rgb2int(game->setup.floor.red,
			game->setup.floor.green, game->setup.floor.blue);
	floor_color = rgb2int(game->setup.ceiling.red,
			game->setup.ceiling.green, game->setup.ceiling.blue);
	y = -1;
	while (++y < WIDTH)
	{
		x = -1;
		while (++x < HEIGHT)
		{
			if (x < HEIGHT / 2)
				my_mlx_pixel_put(&game->img, y, x, sky_color);
			else
				my_mlx_pixel_put(&game->img, y, x, floor_color);
		}
	}
}
