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

void angles_de_ses_morts(t_game *game)
{
	// on init les angles
	int i;
	int j;

	i = 0;
	while(game->map.map[++i])
	{
		j = -1;
		while(game->map.map[++j])
		{
			if(game->map.map[i][j] == 'N')
				set_angle(game, j, i, 'N');
			else if (game->map.map[i][j] == 'S')
				set_angle(game, j, i, 'S');
			else if (game->map.map[i][j] == 'E')
				set_angle(game, j, i, 'E');
			else if (game->map.map[i][j] == 'W')
				set_angle(game, j, i, 'W');
		}
	}
}


int	count_colonnes(t_game *game)
{
	int i;

	i = 0;
	while (game->map.map[i])
		i++;
	return (i);
}


// void exec(t_game *game)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	float angle;
// 	//int ray;
// 	game->map.nb_lignes = count_colonnes(game);
// 	// on compte le nombre de ligne et on creer le rayon quon doit envoyer??
// 	// struct? 
// 	// on part de langle 0 et on lance un rayon
// 	angle = game->player.angle;
// 	while (j > count_colonnes(game)) // on a pas atteint lautre cote de la ligne de colonne) donc len max?)
// 	{
// 		//ray = cast_ray(game, game->player.angle);
// 		j++;
// 	}
// }

int init_ray(t_game *game, t_player *player, int col)
{
	game->ray.mapx = player->x;
	game->ray.mapy = player->y;
	game->ray.camerax = 2 * col / (Double)WIDTH - 1;
	game->ray.dirx = player->dirx + player->planex * (double)game->ray.camerax;
	game->ray.diry = player->diry + player->planey * (double)game->ray.camerax;
	game->ray.deltax = sqrt(1 + (game->ray.diry * game->ray.diry)
			/ (game->ray.dirx * game->ray.dirx));
	game->ray.deltay = sqrt(1 + (game->ray.dirx * game->ray.dirx)
			/ (game->ray.diry * game->ray.diry));
	//switch raycasting
	return (0);
}

int raycasting(t_game *game)
{
	int col;
	
	col = -1;
	while(++col < WIDTH)
	{
		init_ray(game, game->player, col);
	}
	// chercher les murs
}