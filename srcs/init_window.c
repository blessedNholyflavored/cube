/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:12:06 by mmhaya            #+#    #+#             */
/*   Updated: 2022/10/18 15:32:00 by lkhamlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_close(t_game *game)
{
	free(game->window.mlx);
	exit(0);
	return (0);
}

int	ft_get_texture_adress2(t_game *game)
{
	game->assets.ea.addr = mlx_get_data_addr(game->assets.ea.img,
			&game->assets.ea.bits_per_pixel,
			&game->assets.ea.line_length, &game->assets.ea.endian);
	if (!game->assets.no.addr)
		return (1);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel, &game->img.line_length,
			&game->img.endian);
	if (!game->img.addr)
		return (1);
	return (0);
}

int	ft_get_texture_adress(t_game *game)
{
	game->assets.we.addr = mlx_get_data_addr(game->assets.we.img,
			&game->assets.we.bits_per_pixel,
			&game->assets.we.line_length, &game->assets.we.endian);
	if (!game->assets.we.addr)
		return (1);
	game->assets.so.addr = mlx_get_data_addr(game->assets.so.img,
			&game->assets.so.bits_per_pixel,
			&game->assets.so.line_length, &game->assets.so.endian);
	if (!game->assets.so.addr)
		return (1);
	game->assets.no.addr = mlx_get_data_addr(game->assets.no.img,
			&game->assets.no.bits_per_pixel,
			&game->assets.no.line_length, &game->assets.no.endian);
	if (!game->assets.no.addr)
		return (1);
	ft_get_texture_adress2(game);
	return (0);
}

int	set_text(t_game *game)
{
	game->assets.we.img = mlx_xpm_file_to_image(game->window.mlx,
			game->setup.path_we,
			&game->assets.we.width, &game->assets.we.height);
	if (game->assets.we.img == NULL)
		return (1);
	game->assets.so.img = mlx_xpm_file_to_image(game->window.mlx,
			game->setup.path_so,
			&game->assets.so.width, &game->assets.so.height);
	if (game->assets.so.img == NULL)
		return (1);
	game->assets.no.img = mlx_xpm_file_to_image(game->window.mlx,
			game->setup.path_no,
			&game->assets.no.width, &game->assets.no.height);
	if (game->assets.no.img == NULL)
		return (1);
	game->assets.ea.img = mlx_xpm_file_to_image(game->window.mlx,
			game->setup.path_ea,
			&game->assets.ea.width, &game->assets.ea.height);
	if (game->assets.ea.img == NULL)
		return (1);
	game->img.img = mlx_new_image(game->window.mlx, WIDTH, HEIGHT);
	if (game->img.img == NULL)
		return (1);
	return (0);
}

int	test(t_game *game)
{
	raycasting(game);
	return (0);
}

int	init_window(t_game *game)
{
	init_struct_image(game);
	init_dir(game);
	game->window.mlx = mlx_init();
	if (game->window.mlx == NULL)
		return (1);
	game->window.mlx_win = mlx_new_window(game->window.mlx,
			WIDTH, HEIGHT, "Cub3D");
	if (!game->window.mlx_win)
		return (2);
	if (set_text(game) || ft_get_texture_adress(game))
	{
		printf("error\nTexture didn't load\n");
		return (1);
	}
	if (raycasting(game))
		return (1);
	mlx_hook(game->window.mlx_win, 2, 1L << 0, key_codes, game);
	mlx_hook(game->window.mlx_win, 17, 1L << 17, ft_keys, game);
	mlx_loop_hook(game->window.mlx, test, game);
	mlx_loop(game->window.mlx);
	return (0);
}
