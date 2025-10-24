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

void	free_all(t_game *game)
{
	if (!game->map)
		return ;
	if (game->map->fd > 2)
		close(game->map->fd);
	if (game->map->e_fd > 2)
		close(game->map->e_fd);
	if (game->map->n_fd > 2)
		close(game->map->n_fd);
	if (game->map->s_fd > 2)
		close(game->map->s_fd);
	if (game->map->w_fd > 2)
		close(game->map->w_fd);
	if (game->map->north)
		free(game->map->north);
	if (game->map->east)
		free(game->map->east);
	if (game->map->south)
		free(game->map->south);
	if (game->map->west)
		free(game->map->west);
	if (game->map->map)
		free_array(game->map->map);
	if (game->map->copy_map)
		free_array(game->map->copy_map);
	free_game(game);
}
