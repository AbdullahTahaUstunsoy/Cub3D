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
	int		flag;
	char	*north;
	char	*east;
	char	*south;
	char	*west;
	char	*ceiling;
	char	*floor;

}			t_map;

#endif