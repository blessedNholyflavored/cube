/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:39:28 by mmhaya            #+#    #+#             */
/*   Updated: 2022/05/17 14:31:50 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	atoi2(const char *str, long int i, long int k);

int	ft_atoi(const char *str)
{
	long int	i;
	long int	n;
	long int	k;

	i = 0;
	k = 1;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			k = -k;
		i++;
	}
	n = atoi2(str, i, k);
	return (n);
}

static int	atoi2(const char *str, long int i, long int k)
{
	long int	n;

	n = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			n = n * 10 + str[i] - '0';
		else
			break ;
		i++;
	}
	if (n * k > 255 || n * k < 0)
		return (266);
	return (n * k);
}
