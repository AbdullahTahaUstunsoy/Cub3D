#include "../includes/cube3D.h"

//color, r g b kullandım mı ? r << 16, g << 8 , b yapısını şuan göremedim gerekli mi ?
int check_map_name(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = ft_strlen(str);
	if (str[i - 1] != 'b')
		flag = 1;
	else if (str[i - 2] != 'u')
		flag = 1;
	else if (str[i - 3] != 'c')
		flag = 1;
	else if (str[i - 4] != '.')
		flag = 1;
	else if (str[i - 5] == '/') // OLMALI MI OLMAMALAI MI TAHAYA SORRRRRRRRR
		flag = 1;
	if (flag == 1)
		printf("Wrong file name!\n");
	return (flag);
}

void	map_init(t_game *game)
{
	game->map->fd = -2;
	game->map->start_x = -1;
	game->map->start_y = -1;
	game->map->e_fd = -2;
	game->map->s_fd = -2;
	game->map->n_fd = -2;
	game->map->w_fd = -2;
	game->map->map_height = 0;
	game->map->ceiling = -1;
	game->map->floor = -1;
	game->map->north = NULL;
	game->map->south = NULL;
	game->map->east = NULL;
	game->map->west = NULL;
	game->map->player = game->player; // bu saçma mı oldu
}


int main(int ac, char **av)
{
	t_game *game;

	game = init_structs();
	if (check_initial_conditions(game,ac))
		return (1);
	if (map_operations(game,av))
		return (1);
	if (set_game_components(game))
		return (1);
	load_textures(game);
	render(game);
	mlx_loop(game->mlx);
	return (0);
}
