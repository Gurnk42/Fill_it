#ifndef READ_H
# define READ_H

#include "get_next_line.h"
#include "libft.h"

typedef struct	s_map
{
	int			x;
	int			y;
	//char		**map;
	void		*nxt_map;
}				t_map;


t_map	*get_maps(int fd);


#endif
