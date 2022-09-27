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
		game->img = malloc(sizeof(t_img));
		if (!game->img) // free game;
			return (1);
		// if (set_text(game))
        // {
        //     	printf("error\nTexture didn't load\n");
        //        	return (1);
        // }
		// angles, exec et texture
 		mlx_hook(game->window.mlx_win, 2, 1L<<0, key_codes, game);
		mlx_hook(game->window.mlx_win, 17, 1L<<17, ft_keys,game);
		//mlx_loop(game->window.mlx);
		mlx_loop_hook(game->window.mlx, loop, game);
		mlx_loop(game->window.mlx);
        return (0);
}

void	ft_get_texture_adress(t_game *game)
{
	game->texture[0].addr = (int *)mlx_get_data_addr(game->texture[0].img,
			&game->texture[0].bits_per_pixel,
			&game->texture[0].line_length, &game->texture[0].endian);
	game->texture[1].addr = (int *)mlx_get_data_addr(game->texture[1].img,
			&game->texture[1].bits_per_pixel,
			&game->texture[1].line_length, &game->texture[1].endian);
	game->texture[2].addr = (int *)mlx_get_data_addr(game->texture[2].img,
			&game->texture[2].bits_per_pixel,
			&game->texture[2].line_length, &game->texture[2].endian);
	game->texture[3].addr = (int *)mlx_get_data_addr(game->texture[3].img,
			&game->texture[3].bits_per_pixel,
			&game->texture[3].line_length, &game->texture[3].endian);
	// game->texture[4].addr = (int *)mlx_get_data_addr(game->texture[4].img,
	// 		&game->texture[4].bits_per_pixel,
	// 		&game->texture[4].line_length, &game->texture[4].endian);
}

// int     set_text(t_game *game)
// {
// 	game->assets.we.img = mlx_xpm_file_to_image(game->window.mlx, game->setup.path_we,
// 		&game->assets.we.width, &game->assets.we.height);
// 	if (game->assets.we.img == NULL)
//                 return (1);
//         game->assets.so.img = mlx_xpm_file_to_image(game->window.mlx, game->setup.path_so,
// 		&game->assets.so.width, &game->assets.so.height);
// 	if (game->assets.so.img == NULL)
//                 return (1);
//         game->assets.no.img = mlx_xpm_file_to_image(game->window.mlx, game->setup.path_no,
// 		&game->assets.no.width, &game->assets.no.height);
// 	if (game->assets.no.img == NULL)
//                 return (1);
//         game->assets.ea.img = mlx_xpm_file_to_image(game->window.mlx, game->setup.path_ea,
// 		&game->assets.ea.width, &game->assets.ea.height);
//         if (game->assets.ea.img == NULL)
//                 return (1);
// 		ft_get_texture_adress(game);
//         return (0);
// }


void	set_text(t_game *game)
{
	if (!(game->texture[0].img = mlx_xpm_file_to_image(game->window.mlx,
					game->setup.path_no, &(game->texture[0].width),
					&(game->texture[0].height))))
	{
		free(game->no);
		printf("error\n");
	}
		//ft_error(game, "Texture SO\n");
	if (!(game->texture[1].img = mlx_xpm_file_to_image(game->window.mlx,
					game->setup.path_so, &(game->texture[1].width),
					&(game->texture[1].height))))
	{
		free(game->so);
		printf("error\n");
	}//		ft_error(game, "Texture NO\n");
	if (!(game->texture[2].img = mlx_xpm_file_to_image(game->window.mlx,
					game->setup.path_we, &(game->texture[2].width),
					&(game->texture[2].height))))
		{
		free(game->we);
		printf("error\n");
	}		//ft_error(game, "Texture EA\n");
	if (!(game->texture[3].img = mlx_xpm_file_to_image(game->window.mlx,
					game->setup.path_ea, &(game->texture[3].width),
					&(game->texture[3].height))))
	{
		free(game->ea);
		printf("error\n");
	}		//ft_error(game, "Texture WE\n");
	// if (!(game->texture[4].img = mlx_xpm_file_to_image(game->window.mlx,
	// 				game->setup.path_sp, &(game->texture[4].width),
	// 				&(game->texture[4].height))))
	// 	{
	// 	free(game->sp);
	// 	printf("error\n");
	// 	}
		//ft_error(game, "Texture S\n");
	ft_get_texture_adress(game);
}