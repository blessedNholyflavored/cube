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

// void set_angle(t_game *game, int x, int y, char letter)
// {
// 	if (letter == 'E')
// 		game->player.angle = 0; 
// 	if (letter == 'W')
// 		game->player.angle = M_PI;
// 	if (letter == 'S')
// 		game->player.angle = 3 * M_PI_2;
// 	if (letter == 'N')
// 		game->player.angle = M_PI_2;
	// game->player.x = (x * 64) + 32;
	// // raycast de la position = direction x + planeX * cameraX
	// game->player.y = (y * 64) + 32;
//}

// on recupere les angles grace au truc du cercle trigonometrique oe oe oe 
// https://i2.wp.com/www.methodemaths.fr/cercletrigonometrique.jpg?w=584


void init_struct_ray(t_game *game)
{
	game->ray.dirx = 0;
	game->ray.diry = 0;
	game->ray.deltax = 0;
	game->ray.deltay = 0;
	game->ray.side = 0;
	game->ray.PixelLast = 0;
	game->ray.FirstPixel = 0;
	game->ray.sidex = 0;
	game->ray.sidey = 0;
	//game->zbuffer = (double *)malloc(sizeof(double) * WIDTH);
	//	exit(0);
}

int go_chercher_la_distance_du_rayon_mec(t_game *game, t_player *player)
{
	if (game->ray.side == 1)
	{
		//on calcule la distance entre la camera
		game->ray.dist = (game->ray.mapy - player->posy + (1 - game->ray.stepy) / 2) / game->ray.diry;
		game->ray.wallx = player->posx + game->ray.dist * game->ray.dirx;
	}
	else
	{
		game->ray.dist = (game->ray.mapx - player->posx + (1 - game->ray.stepx) / 2) / game->ray.dirx;
		game->ray.wallx = player->posy + game->ray.dist * game->ray.diry;
	}
	game->ray.line_height = (int)(HEIGHT / game->ray.dist); // on calcule la taille de la ligne quon  doit dessiner sur lecran
	game->ray.FirstPixel = -game->ray.line_height / 2 + HEIGHT / 2; // on calcule la pixel la plus basse et plus haute ds la bande
	if (game->ray.FirstPixel < 0)
		game->ray.FirstPixel = 0;
	game->ray.PixelLast = game->ray.line_height / 2 + HEIGHT / 2;
	if (game->ray.PixelLast >= HEIGHT)
		game->ray.PixelLast = HEIGHT - 1;
	
	// la valeur de HEIGHT fait que les murs sont des cubes de taille identik
	return (0);
}

void go_chercher_les_murs(t_game *game) // dda
{
	int mur;

	mur = 0;
	while (mur == 0)
	{
	// on parcour chqe cube soit ds la direction de x ou y
		if (game->ray.sidex < game->ray.sidey)
		{
			game->ray.sidex += game->ray.deltax;
			game->ray.mapx += game->ray.stepx;
			game->ray.side = 0; // + (game->ray.dix < 0);
		}
		else
		{
			game->ray.sidey += game->ray.deltay;
			game->ray.mapy += game->ray.stepy;
			game->ray.side = 1; // + (game->ray.diy > 0);
		}
		
		if (game->map.map[game->ray.mapy][game->ray.mapx] == '1')
		{
			//printf("oui");
			mur = 1;
		}
		// est ce que on a hit un mur ou pas
		// si c ok on passe au calcul de la distance du rayon jusko mur
	}
	//go_chercher_la_distance_du_rayon_mec(game, &game->player);
}

void verification_ray(t_game *game, t_player *player)
{
	// on alcule la distance que le ray doit faire entre son point de depart et le premier croisement avec labcisse et lordonne
	// ces distances sincremente des que le player fait un pas
	if (game->ray.dirx < 0)
	{
		game->ray.stepx = -1;
		game->ray.sidex = (player->posx - game->ray.mapx) * game->ray.deltax;
	}
	else
	{
		game->ray.stepx = 1;
		game->ray.sidex = (game->ray.mapx + 1.0 - player->posx) * game->ray.deltax;
	}
	if (game->ray.diry < 0)
	{
		game->ray.stepy= -1;
		game->ray.sidey = (player->posy - game->ray.mapy) * game->ray.deltay;
	}
	else
	{
		game->ray.stepy = 1;
		game->ray.sidey = (game->ray.mapy + 1.0 - player->posy) * game->ray.deltay;
	}
	//go_chercher_les_murs(game);
}


int init_ray(t_game *game, t_player *player, int col)
{
	game->ray.mapx = (int)player->posx; // ds quelle case de la map suis je
	game->ray.mapy = (int)player->posy;
	game->ray.dist = 0;
	game->ray.camerax = 2 * col / (double)WIDTH - 1;
	// on calcule la taille du ray du point de depart x ou y jusquau prochain croisement de x ou y
	game->ray.dirx = player->dirx + player->planex * (double)game->ray.camerax;
	game->ray.diry = player->diry + player->planey * (double)game->ray.camerax;
	game->ray.deltax = fabs(1 / game->ray.dirx);
	game->ray.deltay = fabs(1 / game->ray.diry);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	img->addr[WIDTH * y + x] = color;
}

// void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }


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

	sky_color = rgb2int(187, 67, 41);//, c->col.rgb_s[1], c->col.rgb_s[2]);
	floor_color = rgb2int(24, 30,218);//c->col.rgb_f[0], c->col.rgb_f[1], c->col.rgb_f[2]);
	y = -1;
	while (++y < WIDTH)
	{
		x = -1;
		while (++x < HEIGHT)
		{
			if (x < HEIGHT / 2)
				my_mlx_pixel_put(game->img, y, x, sky_color);
			else
				my_mlx_pixel_put(game->img, y, x, floor_color);
		}
	}
}

void testing(t_game *game, int x)
{
	int i;
	int color;

	i = game->ray.FirstPixel;
	game->text.step = 1.0 * game->texture[game->ray.side].height /  game->ray.line_height;
	game->text.texpos = (game->ray.FirstPixel - HEIGHT / 2 + game->ray.line_height / 2) * game->text.step;
	while (i < game->ray.PixelLast)
	{
		game->text.texy = (int)game->text.texpos &(game->texture[game->text.texdir].height - 1);
 		game->text.texpos += game->text.step;
		if (game->ray.side % 2)
		color = (color >> 1) & AND_ING;
		my_mlx_pixel_put(game->img, x, i, color);
		i++;
	}
}

// void affichertext(t_game *game, double ty)
// {
// 	int x;
// 	int y;
// 	int textureX;
// 	int textureY;
// 	int d;

// 	x = game->ray.FirstPixel - 1;
// 	while (++x < game->ray.PixelLast)
// 	{
// 		textureX = (int)(BYTE * (x - (-game->ray.line_height / 2 + HEIGHT))
// 					* WIDTH / game->ray.line_height) / BYTE; //////////////////
// 		if (ty >= 0 && x >= 0 && x <= WIDTH)
// 		{
// 			y = game->ray.FirstPixel - 1;
// 			while(++y < game->ray.PixelLast)
// 			{
// 				d = y * BYTE - HEIGHT * (BYTE / 2) + game->img->height * (BYTE / 2);
// 				textureY = abs(((d * HEIGHT) / game->img->height) / BYTE);
// 				game->img->color = game->img->addr[WIDTH * textureX + textureY];
// 				if ((game->img->color & 0x00FFFFFF) != 0)
// 				my_mlx_pixel_put(game->img, x, y, game->img->color);
// 			}
// 		}
// 	}
// }

int raycasting(t_game *game)
{
	int col;
	
	col = -1;
	// while(++col < WIDTH)
	// {
		init_ray(game, &game->player, col);
		verification_ray(game, &game->player);
		go_chercher_les_murs(game);
		go_chercher_la_distance_du_rayon_mec(game, &game->player);
		testing(game, col);
		// draw_px_col(game);//, &game->ray), col);	
	//}

	return(0);

}