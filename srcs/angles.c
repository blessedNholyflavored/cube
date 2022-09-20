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

void set_angle(t_game *game, int x, int y, char letter)
{
	if (letter == 'E')
		game->player.angle = 0; 
	if (letter == 'W')
		game->player.angle = M_PI;
	if (letter == 'S')
		game->player.angle = 3 * M_PI_2;
	if (letter == 'N')
		game->player.angle = M_PI_2;
	game->player.x = (x * 64) + 32;
	// raycast de la position = direction x + planeX * cameraX
	game->player.y = (y * 64) + 32;
}
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

