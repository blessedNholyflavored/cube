/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkhamlac <lkhamlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 15:45:50 by lkhamlac          #+#    #+#             */
/*   Updated: 2022/05/17 14:09:27 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s + i));
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*copy_s;

	i = 0;
	j = 0;
	copy_s = malloc(sizeof(char) * (len + 1));
	if (!copy_s)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
			copy_s[j++] = s[i];
		i++;
	}
	copy_s[j] = '\0';
	return (copy_s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*copy_s;

	i = 0;
	copy_s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!copy_s)
		return (NULL);
	while (s1[i])
	{
		copy_s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		copy_s[i] = s2[j];
		i++;
		j++;
	}
	copy_s[i] = '\0';
	return (copy_s);
}

char	*ft_strdup(char *s1)
{
	char	*cpy;
	int		i;

	cpy = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!cpy)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
