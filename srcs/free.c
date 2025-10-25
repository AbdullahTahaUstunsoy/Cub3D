#include "../includes/cube3D.h"

void *free_game(t_game *game)
{
	if (game->player)
		free(game->player);
	if (game->map)
		free(game->map);
	if (game->ray)
		free(game->ray);
	free(game);
	return (NULL);
}


