//  int	get_px_color(t_img *img, int y, double preci, int line_height)
// {
// 	char	*px;
// 	double	step;
// 	double	x_tex;
// 	double	y_tex;
// 	int		offset;

// 	offset = (line_height - HEIGHT);
// 	step = img->height / (double)line_height;
// 	x_tex = preci * (double)img->width;
// 	y_tex = (double)y * step;
// 	if (line_height > HEIGHT)
// 		y_tex = ((double)(y + offset / 2)) * step;
// 	px = img->addr + ((int)y_tex * img->line_length
// 			+ (int)x_tex * (img->bpp / 8));
// 	return (*(unsigned int *)px);
// }

// void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
// {
// 	char	*dst;

// 	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
// 	*(unsigned int *)dst = color;
// }


// unsigned int	plafond_shade(unsigned int color, int pixel)
// {
// 	unsigned int	c[3];
// 	double			coef_px;
// 	int				max_in;

// 	max_in = HEIGHT / 2;
// 	coef_px = (pixel - 0.0) * (0.25 - 1) / (max_in - 0.0) + 1.0;
// 	c[0] = color >> 16 & 0xff;
// 	c[1] = color >> 8 & 0xff;
// 	c[2] = color & 0xff;
// 	c[0] = ((unsigned int)(c[0] * coef_px)) << 16;
// 	c[1] = ((unsigned int)(c[1] * coef_px)) << 8;
// 	c[2] = ((unsigned int)(c[2] * coef_px));
// 	return (c[0] + c[1] + c[2]);
// }


// unsigned int	sol_shade(unsigned int color, int pixel)
// {
// 	unsigned int	c[3];
// 	double			coef_px;
// 	int				min_in;

// 	min_in = HEIGHT / 2;
// 	coef_px = (pixel - min_in) * (1.0 - 0.25) / (HEIGHT - min_in) + 0.25;
// 	c[0] = color >> 16 & 0xff;
// 	c[1] = color >> 8 & 0xff;
// 	c[2] = color & 0xff;
// 	c[0] = ((unsigned int)(c[0] * coef_px)) << 16;
// 	c[1] = ((unsigned int)(c[1] * coef_px)) << 8;
// 	c[2] = ((unsigned int)(c[2] * coef_px));
// 	return (c[0] + c[1] + c[2]);
// }


// unsigned int	color_shade(t_game *game, unsigned int color)
// {
// 	unsigned int	r;
// 	unsigned int	g;
// 	unsigned int	b;
// 	double			coef;

// 	if (game->ray.dist > 15)
// 		coef = 0.25;
// 	else
// 		coef = 1.0 / ((game->ray.dist - 0.0) * (4.0 - 1.0) / (15.0 - 0.0) + 1.0);
// 	r = color >> 16 & 0xff;
// 	g = color >> 8 & 0xff;
// 	b = color & 0xff;
// 	r = ((unsigned int)(r * coef)) << 16;
// 	g = ((unsigned int)(g * coef)) << 8;
// 	b = ((unsigned int)(b * coef));
// 	return (r + g + b);
// }


// void sol_texture(t_game *game, t_ray *ray, int col, t_img *img)
// {
// 	int				pixel;
// 	int				y;
// 	unsigned int	color;

// 	pixel = ray->FirstPixel - 1;
// 	y = 0;
// 	while (++pixel < ray->PixelLast)
// 	{
// 		if (ray->line_height > HEIGHT)
// 			color = get_px_color(img, y, ray->wallx
// 					- (int)ray->wallx, ray->line_height);
// 		else
// 			color = get_px_color(img, y, ray->wallx
// 					- (int)ray->wallx, ray->line_height);
// 		color = color_shade(game, color);
// 		my_mlx_pixel_put(game->img, col, pixel, color);
// 		y++;
// 	}
// 	while (pixel < HEIGHT)
// 	{
// 		color = sol_shade(game->sol, pixel);
// 		my_mlx_pixel_put(game->img, col, pixel, color);
// 		pixel++;
// 	}
// }
