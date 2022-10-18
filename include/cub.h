/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:10:30 by mmhaya            #+#    #+#             */
/*   Updated: 2022/10/18 15:21:48 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
#include "../minilibx/mlx.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>

#define WIDTH 1280 // pas trop grand pck faut pas deconner
#define HEIGHT 720

typedef enum e_last
{
	HAUT,
	BAS,
	GAUCHE,
	DROITE
}			t_last;

typedef enum e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}			t_dir;

typedef struct s_map
{
	int		x;
	int		y;
	int		fd;
	int		len_max;
	int		max_y;
	char	**file;
	char	**map;
}			t_map;

typedef struct s_check
{
	int	start_x;
	int	start_y;
	int	largeur_max;
	int	n;
	int	s;
	int	w;
	int	e;
	int	f;
	int	c;
	int sp;
}			t_check;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}			t_color;

typedef struct s_setup
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char 	*path_sp;
	t_color	floor;
	t_color	ceiling;
}			t_setup;

typedef struct s_player
{
	int	dir;
	double	posx;
	double	posy;
	double	planex;
	double	planey;
	double	dirx;
	double	diry;
	
}			t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	int		bits_per_pixel;
}			t_img;

typedef struct s_assets
{
	t_img	we;
	t_img	so;
	t_img	no;
	t_img	ea;
}			t_assets;

typedef struct s_window
{
	void	*mlx_win;
	void	*mlx;
}			t_window;

typedef struct s_ray
{
		double camerax;
	double dirx;
	double diry;
	int mapx;
	int mapy;
	double sidey;
	double sidex;
	double deltax;
	double deltay;
	double perpalldist;
	int stepx;
	int stepy;
	int	side;
	double wallx;
	int sidewall;
	int line_height;
	int		FirstPixel;
	int		PixelLast;
	int		x;
}			t_ray;


typedef struct s_game
{
	char *	we;
	char *	so;
	char *	no;
	char *	ea;
	t_player	player;
	t_setup		setup;
	t_check		check;
	t_map		map;
	t_img		img;
	t_assets	assets;
	t_window	window;
	t_ray		ray;
}			t_game;

int		check_map(t_game *game);
int		check_char(t_game *game, char **map);
int	check_dir(double x, double y, char c, t_game *game);
char	**ft_get_file(int fd, int lvl);
int		get_next_line(int fd, char **line);
char	*ft_stock_line(char *str, char **line);
char	*ft_get_static(char *str, char buf[80], int len);
char	*ft_strdup(char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
int		check_dim(t_game *game);
void	free_all(t_game *game);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	init_struct(t_game *game);
int		parsing_map(t_game *game, int ac, char **av);
int		ft_strlen_space(char *str);
int		check_rgb(t_game *game, int *i, int y, char type);
int		check_fl(t_game *game, char **file, int *x, int y);
int		check_ce(t_game *game, char **file, int *x, int y);
int		check_ea(t_game *game, char **file, int *x, int y);
int		check_we(t_game *game, char **file, int *x, int y);
int		check_no(t_game *game, char **file, int *x, int y);
int		check_so(t_game *game, char **file, int *x, int y);
int		find_arg(t_game *game, char **file, int *x, int y);
int		check_setup(t_game *game);
int		check_arg(t_game *game, char *av);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *str);
int		init_map(t_game *game, int y);
int		find_map(char** file, int y);
void	copy_map(t_game *game, char **file, int i, int x);
int		set_map(t_game *game, char **file, int y);
int		init_map(t_game *game, int y);
int		final_check(t_game *game);
int     init_window(t_game *game);
void	init_dir(t_game *game);
void 	angles_de_ses_morts(t_game *game);
void	exec(t_game *game);
int		raycasting(t_game *game);
int		loop(t_game *game);
int		ft_get_texture_adress(t_game *game);
int		set_text(t_game *game);
void	texture_colonne(t_game *game);
void	init_struct_ray(t_game *game);
void	get_texture(t_game *game);
void	draw_shit(t_game *game, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_sky_floor_colors(t_game *game);
void	affichertext(t_game *game, double ty);
void	testing(t_game *game, int x);
void	move_cam_right(t_game *game);
void	move_cam_left(t_game *game);
void	move_ahead(t_game *game);
void	move_back(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	move_cam_right(t_game *game);
void	move_cam_left(t_game *game);

#endif