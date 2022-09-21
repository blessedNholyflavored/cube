/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 10:12:06 by mmhaya            #+#    #+#             */
/*   Updated: 2022/07/07 16:49:03 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int ft_close(t_game *game)
{
	free(game->window.mlx);
	exit(0);
	return (0);
}


int key_codes(int keycode, t_game *game)
{
	if (keycode == 65307)
		ft_close(game);
	return (1);
}

int ft_keys(t_game *game)
{
	free(game->window.mlx);
	exit(0);
	// if (game->window.img)
	// 	mlx_destroy_image(game->window.mlx, game->window.mlx);
	// if (game->window.win)
	// 	mlx_destroy_window(game->window.mlx, game->window.mlx);
	// if (game->window.mlx)
	// 	mlx_destroy_display(game->window.mlx);
	return (0);
}

int     init_window(t_game *game)
{
        game->window.mlx = mlx_init();
        if (game->window.mlx == NULL)
                return (1);
        game->window.mlx_win = mlx_new_window(game->window.mlx, WIDTH, HEIGHT, "Cub3D");
        if (!game->window.mlx_win)
                return(1);
        if (set_text(game	))
        {
                printf("error\nTexture didn't load\n");
                return (1);
        }
		// angles, exec et texture
		angles_de_ses_morts(game);
		exec(game);
		mlx_hook(game->window.mlx_win, 2, 1L<<0, key_codes, game);
		mlx_hook(game->window.mlx_win, 17, 1L<<17, ft_keys,game);
		mlx_loop(game->window.mlx);
        return (0);
}

int     set_text(t_game *game)
{
	game->assets.we.img = mlx_xpm_file_to_image(game->window.mlx, game->setup.path_we,
		&game->assets.we.width, &game->assets.we.height);
	if (game->assets.we.img == NULL)
                return (1);
        game->assets.so.img = mlx_xpm_file_to_image(game->window.mlx, game->setup.path_so,
		&game->assets.so.width, &game->assets.so.height);
	if (game->assets.so.img == NULL)
                return (1);
        game->assets.no.img = mlx_xpm_file_to_image(game->window.mlx, game->setup.path_no,
		&game->assets.no.width, &game->assets.no.height);
	if (game->assets.no.img == NULL)
                return (1);
        game->assets.ea.img = mlx_xpm_file_to_image(game->window.mlx, game->setup.path_ea,
		&game->assets.ea.width, &game->assets.ea.height);
        if (game->assets.ea.img == NULL)
                return (1);
        return (0);
}
