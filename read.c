/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 13:44:36 by ebouther          #+#    #+#             */
/*   Updated: 2015/11/29 14:12:04 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

static int	ft_new_struct(t_map **map)
{
	if (!((*map)->nxt_map = (t_map *)malloc(sizeof(**map))))
		return (-1);
	(*map) = (*map)->nxt_map;
	(*map)->nxt_map = NULL;
	(*map)->x = 0;
	(*map)->y = 0;
	(*map)->content = ft_strnew(0);
	return (0);
}

static int	ft_nb_occur(char *line, int c, int *first_pos)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	*first_pos = 0;
	if (!line)
		return (-1);
	while (line[i])
	{
		if (line[i] == c)
		{
			if (*first_pos == 0)
				*first_pos = i;
			len++;
		}
		i++;
	}
	return (len);
}

static void	ft_getxy(t_map **map, t_env *env, char *line, int c)
{
	int			pos;
	int			nb;

	pos = 0;
	nb = ft_nb_occur(line, c, &pos);
	if (nb > (*map)->x)
		(*map)->x = nb;
	if (nb > 0)
		(*map)->y++;
	if (nb == 2 && env->last_x == 2 && env->last_pos != 0
			&& (pos != env->last_pos))
		(*map)->x++;
	env->last_x = (*map)->x;
	env->last_pos = pos;
}

static int	ft_fill_struct(t_map **map, int fd)
{
	char	*line;
	t_env	env;

	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) != 4 && ft_strlen(line) != 0)
			return (-1);
		else
			(*map)->content = ft_strjoin((*map)->content, line);
		if (ft_strlen(line) > 0)
			ft_getxy(map, &env, line, '#');
		else
		{
			env.last_pos = 0;
			if (ft_new_struct(map) == -1)
				return (-1);
		}
	}
	return (0);
}

t_map		*ft_get_maps(int fd)
{
	t_map	*map;
	t_map	*beg;

	if (fd < 0 || !(map = (t_map *)malloc(sizeof(*map))))
		return (NULL);
	beg = map;
	map->nxt_map = NULL;
	map->x = 0;
	map->y = 0;
	map->content = ft_strnew(0);
	if (ft_fill_struct(&map, fd) == -1)
		return (NULL);
	return (beg);
}
