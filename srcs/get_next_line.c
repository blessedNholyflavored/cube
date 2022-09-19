/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmhaya <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 15:45:54 by mmhaya            #+#    #+#             */
/*   Updated: 2022/05/17 14:07:15 by mmhaya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*ft_get_static(char *str, char buf[80], int len)
{
	char	*tmp;

	buf[len] = '\0';
	if (!str)
	{
		str = ft_strdup(buf);
		if (!str)
			return (NULL);
	}
	else if (str)
	{
		tmp = str;
		str = ft_strjoin(str, buf);
		if (!str)
			return (NULL);
		free(tmp);
	}
	return (str);
}

char	*ft_stock_line(char *str, char **line)
{
	size_t	i;
	size_t	len;
	char	*tmp;

	i = 0;
	len = ft_strlen(str);
	while (str[i] != '\n' && str[i])
		i++;
	if (i < len)
	{
		*line = ft_substr(str, 0, i);
		if (!(*line))
			return (NULL);
		tmp = str;
		str = ft_substr(str, i + 1, len);
		if (!str)
			return (NULL);
		free(tmp);
	}
	else
	{
		*line = str;
		str = NULL;
	}
	return (str);
}

int	get_next_line(int fd, char **line)
{
	int				len;
	char			buf[80 + 1];
	static char		*str;

	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (-1);
	len = read(fd, buf, 80);
	while (len > 0)
	{
		str = ft_get_static(str, buf, len);
		if (ft_strchr(str, '\n'))
			break ;
		len = read(fd, buf, 80);
	}
	if (!str)
	{
		*line = ft_strdup("");
		return (0);
	}
	str = ft_stock_line(str, line);
	if (!str)
		return (0);
	return (1);
}

char	**ft_get_file(int fd, int lvl)
{
	char	*line;
	char	**tab;

	line = NULL;
	if (get_next_line(fd, &line) == 1)
	{
		tab = ft_get_file(fd, lvl + 1);
		if (!tab)
			return (NULL);
	}
	else
	{
		tab = malloc(sizeof(char *) * (lvl + 2));
		if (!tab)
			return (NULL);
		tab[lvl + 1] = NULL;
	}
	tab[lvl] = line;
	return (tab);
}
