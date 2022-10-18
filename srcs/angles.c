 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 16:57:18 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/09/19 17:00:55 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void go_chercher_la_distance_du_rayon_mec(t_game *game)
{

	if (!game->ray.side)
	{
		game->ray.perpalldist = (game->ray.sidex - game->ray.deltax);
		game->ray.wallx = game->player.posy + game->ray.perpalldist * game->ray.diry;
	}
	else
	{
		game->ray.wallx = game->player.posx + game->ray.perpalldist * game->ray.dirx;
		game->ray.perpalldist = (game->ray.sidey - game->ray.deltay);
	}

}

void go_chercher_les_murs(t_game *game) // dda
{
	int mur;

	mur = 0;
	while (!mur)
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
			mur = 1;
		}
	}
}

void verification_ray(t_game *game)
{

	// on alcule la distance que le ray doit faire entre son point de depart et le premier croisement avec labcisse et lordonne
	// ces distances sincremente des que le player fait un pas
	//printf("posx= = %f, mapx = %d, deltax = %f\n", player->posx, game->ray.mapx, game->ray.deltax);
	if (game->ray.dirx < 0)
	{
		game->ray.stepx = -1;
		game->ray.sidex = (game->player.posx - game->ray.mapx) * game->ray.deltax;
	}
	else
	{
		game->ray.stepx = 1;
		game->ray.sidex = (game->ray.mapx + 1 - game->player.posx) * game->ray.deltax;
	}
	if (game->ray.diry < 0)
	{
		game->ray.stepy= -1;
		game->ray.sidey = (game->player.posy - game->ray.mapy) * game->ray.deltay;
	}
	else
	{
		game->ray.stepy = 1;
		game->ray.sidey = (game->ray.mapy + 1 - game->player.posy) * game->ray.deltay;
	}
}

void dir_touched_wall(t_game *game)
{
	if (game->ray.side == 0 && game->ray.dirx > 0)
		game->ray.sidewall = EAST;
	else if (game->ray.side == 0 && game->ray.dirx <= 0)
		game->ray.sidewall = WEST;
	else if (game->ray.side == 1 && game->ray.diry > 0)
		game->ray.sidewall = SOUTH;
	else
		game->ray.sidewall = NORTH;
}


int init_ray(t_game *game, int col)
{
	game->ray.camerax = 2 * col / (double)WIDTH - 1;
	game->ray.dirx = game->player.dirx + game->player.planex * game->ray.camerax;
	game->ray.diry = game->player.diry + game->player.planey * game->ray.camerax;
	game->ray.deltax = fabs(1 / game->ray.dirx);
	game->ray.deltay = fabs(1 / game->ray.diry);
	game->ray.mapx = game->player.posx; // ds quelle case de la map suis je
	game->ray.mapy = game->player.posy;
 	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

	sky_color = rgb2int(game->setup.floor.red, game->setup.floor.green, game->setup.floor.blue);
	floor_color = rgb2int(game->setup.ceiling.red, game->setup.ceiling.green, game->setup.ceiling.blue);
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



t_img *get_enum(t_game *game)
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


void    wall_pixel_put(t_game *game, int x, int y)
{
    int        px;
    int        px2;
    int        x2;
    int        y2;
    t_img    *print_wall;

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



void texture_colonne(t_game *game) 
{
    t_img    *print_wall;
	
    print_wall = get_enum(game);
	game->ray.line_height = (int)(HEIGHT / game->ray.perpalldist); // on calcule la taille de la ligne quon  doit dessiner sur lecran
	game->ray.FirstPixel = -game->ray.line_height / 2 + HEIGHT / 2; // on calcule la pixel la plus basse et plus haute ds la bande
	if (game->ray.FirstPixel < 0)
		game->ray.FirstPixel = 0;
	game->ray.PixelLast = game->ray.line_height / 2 + HEIGHT / 2;
	if (game->ray.PixelLast >= HEIGHT)
		game->ray.PixelLast = HEIGHT;
}


int raycasting(t_game *game)
{
	int col;
	int px;

	col = 0;
	draw_sky_floor_colors(game);		
	while(col < WIDTH)
	{
		init_ray(game, col);
		verification_ray(game);
		go_chercher_les_murs(game);
		go_chercher_la_distance_du_rayon_mec(game);
		dir_touched_wall(game);
		texture_colonne(game);
		game->ray.wallx -= floor(game->ray.wallx);
		px = game->ray.FirstPixel;
		while(px < game->ray.PixelLast)
			wall_pixel_put(game, col, px++);
		col++;
	}
	mlx_put_image_to_window(game->window.mlx, game->window.mlx_win, game->img.img, 0, 0);
	return(0);

}