#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "../get_next_line/get_next_line.h"

typedef struct s_player
{
	char player_dir; // oyuncunun yönünü tutacak -> N,S,E,W
	double pos_x; // oyuncunun x koordinatı //bunlar henüz bulunmadı sanırım 
	double pos_y; // oyuncunun y koordinatı //bunlar henüz bulunmadı sanırım 
	double plane_x; // kamera düzlemi x bileşeni
	double plane_y; // kamera düzlemi y bileşeni
	double dir_x; // yön vektörünün x bileşeni
	double dir_y; // yön vektörünün y bileşeni
	double move_speed;
	double rotation_speed;	
}           t_player;

typedef struct s_map
{
	int			fd;
	int			e_fd;
	int			n_fd;
	int			s_fd;
	int			w_fd;
	int			flag;
	char		*north;
	char		*east;
	char		*south;
	char		*west;
	int			ceiling;
	int			floor;
	int			map_height;
	char		**map;
	char		**copy_map;
	t_player	*player;

}				t_map;


int fill_map_struct(char *map_file, t_map *map);
void	free_array(char **str);
int	map_fill(t_map *map, char *line, int map_size);
int	map_control(t_map *map);
char	**copy_map(t_map *map);
int	find_player_position(t_map *map);
void	flood_fill(t_map *map, int x, int y, char target, char fill);
int		flood_check(t_map *map, int x, int y);

#endif