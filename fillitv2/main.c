#include "read.h"
#include <fcntl.h>

int main(int ac, char **av)
{
	t_map	*map;
	int		fd;

	if (ac == 3)
	{
		fd = open(av[1], O_RDONLY);

		map = ft_get_maps(fd, ft_atoi(av[2]));
		while (map)
		{
			ft_putstr(map->content);
			//ft_putnbr(map->x);
			ft_putchar('\n');
			//ft_putnbr(map->y);
			//ft_putchar('\n');
			//ft_putchar('\n');
			map = map->nxt_map;
		}
		close(fd);
	}
	return (0);
}
