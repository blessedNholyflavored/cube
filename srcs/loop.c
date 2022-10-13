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


// void texture_colonne(t_game *game, t_ray *ray, int col, char direction)
// {
// 	int pixel;
// 	unsigned int color;
// 	t_img *img;

// 	if (direction == 'N')
// 		img = &game->texture[0];
// 	else if (direction == 'S')
// 		img = &game->texture[1];
// 	else if (direction == 'E')
// 		img = &game->texture[2];
// 	else
// 		img = &game->texture[3];
// 	if (ray->FirstPixel > 0)
// 	{
// 		pixel = -1;
// 		while (++pixel < ray->FirstPixel)
// 		{
// 			color = plafond_shade(game->plafond, pixel);
// 			my_mlx_pixel_put(game->img, col, pixel, color);
// 		}
// 	}
// 	//sol_texture(game, ray, col, img);
// }


void	init_texture(t_game *game)
{
	if (game->ray.side == 0 && game->ray.dirx < 0)
		game->text.texdir = 0;
	if (game->ray.side == 0 && game->ray.dirx >= 0)
		game->text.texdir = 1;
	if (game->ray.side == 1 && game->ray.diry < 0)
		game->text.texdir = 2;
	if (game->ray.side == 1 && game->ray.diry >= 0)
		game->text.texdir = 3;
	if (game->ray.side == 0)
		game->text.wallx = game->player.posy + game->ray.dist \
						* game->ray.diry;
	else
		game->text.wallx = game->player.posx + game->ray.dist \
						* game->ray.dirx;
	game->text.wallx -= floor((game->text.wallx));
}


// void draw_shit(t_game *game, int x, int y)
// {
// 	y = game->ray.FirstPixel - 1;
// 	init_texture(game);
// 	game->text.step = 1.0 * game->texture[game->text.texdir].height  / game->ray.line_height;
// 	//om choppe coordonnees de textures
// 	game->text.texx = (int)(game->text.wallx * (double)game->texture[game->text.texdir].width);
// 	if (game->ray.side == 0 && game->ray.dirx > 0)
// 		game->text.texx = game->texture[game->text.texdir].width - game->text.texx - 1;
// 	if (game->ray.side == 1 && game->ray.diry < 0)
// 		game->text.texx = game->texture[game->text.texdir].width - game->text.texx - 1;
// 	game->text.texpos = (game->ray.FirstPixel - HEIGHT / 2 + game->ray.line_height / 2) * game->text.step;
// 	while (++y <= game->ray.PixelLast)
// 	{
// 		game->text.texy = (int)game->text.texpos &(game->texture[game->text.texdir].height - 1);
// 		game->text.texpos += game->text.step;

// 		if (y < HEIGHT && x < WIDTH)
// 			game->img->addr[y * game->img->line_length / 4 + x] =
// 				game->img[game->text.texdir].addr[game->text.texy * //normalement img au lieu de texture
// 					game->img[game->text.texdir].line_length / 4 + game->text.texx];
// 	}
// }


int loop(t_game *game)
{
	int x = -1;
	set_text(game);//proteger fonction
	init_struct_ray(game);
	game->img->img = mlx_new_image(game->window.mlx, WIDTH, HEIGHT);
	game->img->addr = (int *)mlx_get_data_addr(game->img->img, &game->img->bits_per_pixel,
			&game->img->line_length, &game->img->endian);

	draw_px_col(game);//, &game->ray), col);		
	while (++x < WIDTH)
		raycasting(game);
	//affichertext(game, x);
	testing(game, x);	

	
	mlx_put_image_to_window(game->window.mlx, game->window.mlx_win, game->img->img, 0, 0);
	mlx_destroy_image(game->window.mlx, game->img->img);
	return (0);
}