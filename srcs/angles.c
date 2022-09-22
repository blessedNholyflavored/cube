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

// void angles_de_ses_morts(t_game *game)
// {
// 	// on init les angles
// 	int i;
// 	int j;

// 	i = 0;
// 	while(game->map.map[++i])
// 	{
// 		j = -1;
// 		while(game->map.map[++j])
// 		{
// 			if(game->map.map[i][j] == 'N')
// 				set_angle(game, j, i, 'N');
// 			else if (game->map.map[i][j] == 'S')
// 				set_angle(game, j, i, 'S');
// 			else if (game->map.map[i][j] == 'E')
// 				set_angle(game, j, i, 'E');
// 			else if (game->map.map[i][j] == 'W')
// 				set_angle(game, j, i, 'W');
// 		}
// 	}
// }


// int	count_colonnes(t_game *game)
// {
// 	int i;

// 	i = 0;
// 	while (game->map.map[i])
// 		i++;
// 	return (i);
// }

/*
Trouver le premier point d’intersection sur X (X1)
Trouver le multiplicateur (Ya : + le rayon est orienté vers le bas, - il est orienté vers le haut)
Trouver la distance entre deux points d’intersection sur X (X2-X1 donne Xa)
Tant que le prochain point d’intersection n’est pas un mur (pas une case remplie avec un 0) on vérifie le prochain point d’intersection (X2 * Xa, Ya * Ya).
si c’est le cas on arrête la vérification et on calcule la distance parcourue par le rayon
*/

int go_chercher_la_distance_du_rayon_mec(t_ray *ray, t_player *player)
{
	if (ray->side == 1)
	{
		//on calcule la distance entre la camera
		ray->dist = (ray->mapy - player->posy + (1 - ray->stepy) / 2) / ray->diry;
		ray->wallx = player->posx + ray->dist * ray->dirx;
	}
	else
	{
		ray->dist = (ray->mapx - player->posx + (1 - ray->stepx) / 2) / ray->dirx;
		ray->wallx = player->posy + ray->dist * ray->diry;
	}
	ray->line_height = (int)(HEIGHT / ray->dist); // on calcule la taille de la ligne quon  doit dessiner sur lecran
	ray->FirstPixel = -ray->line_height / 2 + HEIGHT / 2; // on calcule la pixel la plus basse et plus haute ds la bande
	if (ray->FirstPixel < 0)
		ray->FirstPixel = 0;
	ray->PixelLast = ray->line_height / 2 + HEIGHT / 2;
	if (ray->PixelLast >= HEIGHT)
		ray->PixelLast = HEIGHT - 1;
	// la valeur de HEIGHT fait que les murs sont des cubes de taille identik
	return (0);
}

int go_chercher_les_murs(t_ray *ray, t_map *map)
{
	int mur;

	mur = 0;
	while (mur == 0)
	{
	// on parcour chqe cube soit ds la direction de x ou y
		if (ray->sidex < ray->sidey)
		{
			ray->sidex += ray->deltax;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidey += ray->deltay;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (map->map[ray->mapx][ray->mapy] > 0) 
			mur = 1;
		// est ce que on a hit un mur ou pas
		// si c ok on passe au calcul de la distance du rayon jusko mur
	}
	return (0);
}

int verification_ray(t_ray *ray, t_player *player)
{
	// on alcule la distance que le ray doit faire entre son point de depart et le premier croisement avec labcisse et lordonne
	// ces distances sincremente des que le player fait un pas
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->sidex = (player->posx - ray->mapx) * ray->deltax;
	}
	else
	{
		ray->stepx = 1;
		ray->sidex = (ray->mapx + 1.0 - player->posx) * ray->deltax;
	}
	if (ray->diry < 0)
	{
		ray->stepy= -1;
		ray->sidey = (player->posy - ray->mapy) * ray->deltay;
	}
	else
	{
		ray->stepy = 1;
		ray->sidey = (ray->mapy + 1.0 - player->posy) * ray->deltay;
	}
	return (0);
}


int init_ray(t_game *game, t_player *player, int col)
{
	//tuto
	game->ray.mapx = (int)player->posx; // ds quelle case de la map suis je
	game->ray.mapy = (int)player->posy;
	game->ray.camerax = 2 * col / (double)WIDTH - 1;
	// on calcule la taille du ray du point de depart x ou y jusquau prochain croisement de x ou y
	game->ray.dirx = player->dirx + player->planex * (double)game->ray.camerax;
	game->ray.diry = player->diry + player->planey * (double)game->ray.camerax; 
	game->ray.deltax = sqrt(1 + (game->ray.diry * game->ray.diry)
			/ (game->ray.dirx * game->ray.dirx));
	game->ray.deltay = sqrt(1 + (game->ray.dirx * game->ray.dirx)
			/ (game->ray.diry * game->ray.diry));
	verification_ray(&game->ray, player);
	return (0);
}

int raycasting(t_game *game)
{
	int col;
	
	col = -1;
	while(++col < WIDTH)
	{
		if (init_ray(game, &game->player, col) == -2)
			return (-2); // faut proteger cette fonction
	
	go_chercher_les_murs(&game->ray, &game->map);
	go_chercher_la_distance_du_rayon_mec(&game->ray, &game->player);
	// its about to go down

// 	if (game->ray.side == 0 && game->ray.dirx > 0)
// 		texture_colonne(game, &game->ray, col, 'E');
// 	else if (game->ray.side == 0 && game->ray.dirx <= 0)
// 		texture_colonne(game, &game->ray, col, 'W');
// 	else if (game->ray.side == 1 && game->ray.dirx > 0)
// 		texture_colonne(game, &game->ray, col, 'S');
// 	else if (game->ray.side == 1 && game->ray.dirx <= 0)
// 		texture_colonne(game, &game->ray, col, 'N');

	}
	return(0);
}