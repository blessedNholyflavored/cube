/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:03:33 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/09/22 16:03:36 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


	// int pixel;
	// unsigned int color;
	// t_img *img;

	// if (direction == 'N')
	// 	img = &game->texture[0];
	// else if (direction == 'S')
	// 	img = &game->texture[1];
	// else if (direction == 'E')
	// 	img = &game->texture[2];
	// else
	// 	img = &game->texture[3];
	// if (ray->FirstPixel > 0)
	// {
	// 	pixel = -1;
	// 	while (++pixel < ray->FirstPixel)
	// 	{
	// 		color = plafond_shade(game->plafond, pixel);
	// 		my_mlx_pixel_put(game->img, col, pixel, color);
	// 	}
	// }
	// sol_texture(game, ray, col, img);


void texture_colonne(t_game *game, t_ray *ray)
{

	//int texture = game->map.map[game->ray.mapx][game->ray.mapy] - 1;
	if (ray->side == 0)
		ray->wallx = game->player.posy + ray->dist * ray->diry;
	else
		ray->wallx = game->player.posx + ray->dist * ray->dirx;
	ray->wallx -= floor(ray->wallx);
}






int loop(t_game *game)
{
	{
	game->img->img = mlx_new_image(game->window.mlx, WIDTH, HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->bpp,
			&game->img->line_length, &game->img->endian);
	raycasting(game);
	mlx_put_image_to_window(game->window.mlx, game->window.mlx_win, game->img->img, 0, 0);
	mlx_destroy_image(game->window.mlx, game->img->img);
	return (0);
}
}