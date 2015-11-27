/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 13:44:36 by ebouther          #+#    #+#             */
/*   Updated: 2015/11/27 14:33:34 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"

t_map	*get_maps(int fd)
{
	t_map	*map;
	t_map	*beg;

	char	*line;
	if (fd < 0 || !(map = (t_map *)malloc(sizeof(*map))))
		return (NULL);
	beg = map;
	map->nxt_map = NULL;
	map->x = 0;
	map->y = 0;
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) > 0)
			map->x = ft_strlen(line);
		else
		{
			if (!(map->nxt_map = (t_map *)malloc(sizeof(*map))))
				return (NULL);
			map = map->nxt_map;
			map->nxt_map = NULL;
			map->y = -1;
		}
		map->y++;
	}
	return (beg);
}


#include <fcntl.h>
int main(int ac, char **av)
{
	t_map	*map;
	int		fd;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);

		map = get_maps(fd);
		while (map->nxt_map)
		{
			ft_putnbr(map->x);
			ft_putchar('\n');
			ft_putnbr(map->y);
			ft_putchar('\n');
			ft_putchar('\n');
			map = map->nxt_map;
		}
		close(fd);
	}
	return (0);
}

