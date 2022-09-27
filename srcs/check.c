/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <mmhaya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:47:51 by mmhaya            #+#    #+#             */
/*   Updated: 2022/05/23 15:49:37 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_strlen_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

int	final_check(t_game *game)
{
	if (game->check.n != 1 || game->check.s != 1 || game->check.w != 1 //||  game->check.sp != 1 
			|| game->check.e != 1 || game->check.f != 1 || game->check.c != 1)
		return (1);
	return (0);
}
