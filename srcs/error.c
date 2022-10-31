/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:13:12 by mmhaya            #+#    #+#             */
/*   Updated: 2022/10/19 19:14:28 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_error2(t_game *game, int i)
{
	if (i == 1)
	{
		printf("error\nbad type of arguments\n");
		exit(0);
	}
	else if (i == 2)
	{
		printf("error\ncheck your arguments\n");
		exit(0);
	}
	else if (i == 3)
	{
		printf("error\ndont trick the .cub rule\n");
		exit(0);
	}
	else if (i == 4)
	{
		printf("cant open the file\n");
		ft_exit(game);
	}
	return (0);
}

int	ft_error3(t_game *game, int i)
{
	if (i == 1)
	{
		printf("error\ncan't get the file\n");
		ft_exit(game);
	}
	else if (i == 2)
	{
		printf("error\nsomething is  in your map settings\n");
		ft_exit(game);
	}
	else if (i == 3)
	{
		printf("error\nmap not found\n");
		ft_exit(game);
	}
	return (0);
}

int	ft_error(t_game *game, int i)
{
	if (i == 1)
	{
		printf("error\nThe map isnt close\n");
		ft_exit(game);
	}
	else if (i == 2)
	{
		printf("error\nInvalid map forbidden carractere detected\n");
		ft_exit(game);
	}
	else if (i == 3)
	{
		printf("error\nTo many players detected in the map\n");
		ft_exit(game);
	}
	return (0);
}
