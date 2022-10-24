/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mmhaya <Mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 23:14:05 by Mmhaya            #+#    #+#             */
/*   Updated: 2022/10/19 00:17:21 by Mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	set_keys(t_game *game)
{
	game->key.key_a = 0;
	game->key.key_d = 0;
	game->key.key_w = 0;
	game->key.key_s = 0;
	game->key.key_left = 0;
	game->key.key_right = 0;
	game->key.key_escape = 0;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == 97)
		game->key.key_a = 1;
	if (keycode == 100)
		game->key.key_d = 1;
	if (keycode == 119)
		game->key.key_w = 1;
	if (keycode == 115)
		game->key.key_s = 1;
	if (keycode == 65361)
		game->key.key_left = 1;
	if (keycode == 65363)
		game->key.key_right = 1;
	if (keycode == 65307)
		game->key.key_escape = 1;
	return (1);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == 97)
		game->key.key_a = 0;
	if (keycode == 100)
		game->key.key_d = 0;
	if (keycode == 119)
		game->key.key_w = 0;
	if (keycode == 115)
		game->key.key_s = 0;
	if (keycode == 65361)
		game->key.key_left = 0;
	if (keycode == 65363)
		game->key.key_right = 0;
	if (keycode == 65307)
		game->key.key_escape = 0;
	return (1);
}

void	exec_key(t_game *game)
{
	if (game->key.key_w)
		move_ahead(game);
	if (game->key.key_s)
		move_back(game);
	if (game->key.key_a)
		move_left(game);
	if (game->key.key_d)
		move_right(game);
	if (game->key.key_left)
		move_cam_left(game);
	if (game->key.key_right)
		move_cam_right(game);
	if (game->key.key_escape)
		ft_exit(game);
}
