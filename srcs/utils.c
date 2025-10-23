#include "../includes/cube3D.h"

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_all(t_map *map)
{
	if (!map)
		return ;
	if (map->fd > 2)
		close(map->fd);
	if (map->e_fd > 2)
		close(map->e_fd);
	if (map->n_fd > 2)
		close(map->n_fd);
	if (map->s_fd > 2)
		close(map->s_fd);
	if (map->w_fd > 2)
		close(map->w_fd);
	if (map->north)
		free(map->north);
	if (map->east)
		free(map->east);
	if (map->south)
		free(map->south);
	if (map->west)
		free(map->west);
	if (map->map)
		free_array(map->map);
	if (map->copy_map)
		free_array(map->copy_map);
	if (map->player)
		free(map->player);
	free(map);
}
