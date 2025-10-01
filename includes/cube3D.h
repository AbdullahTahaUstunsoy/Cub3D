#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "../get_next_line/get_next_line.h"


typedef struct s_map
{
	int		fd;
	int		e_fd;
	int		n_fd;
	int		s_fd;
	int		w_fd;
	int		flag;
	char	*north;
	char	*east;
	char	*south;
	char	*west;
	int		ceiling;
	int		floor;

}			t_map;


int fill_map_struct(char *map_file, t_map *map);
void	free_array(char **str);
#endif