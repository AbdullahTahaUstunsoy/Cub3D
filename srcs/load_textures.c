#include "../includes/cube3D.h"

void load_textures(t_game *game)
{
	//NULL kontrollerini ekle
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx, game->map->north, //textures[0] -> North texture , textures[1] -> South texture , textures[2] -> East texture , textures[3] -> West texture
			&game->textures[0].width, &game->textures[0].height);
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img,
			&game->textures[0].bits_per_pixel, &game->textures[0].line_length,
			&game->textures[0].endian);
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx, game->map->south,
			&game->textures[1].width, &game->textures[1].height);
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].img,
			&game->textures[1].bits_per_pixel, &game->textures[1].line_length,
			&game->textures[1].endian);
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx, game->map->east,
			&game->textures[2].width, &game->textures[2].height);
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].img,
			&game->textures[2].bits_per_pixel, &game->textures[2].line_length,
			&game->textures[2].endian);
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx, game->map->west,
			&game->textures[3].width, &game->textures[3].height);
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].img,
			&game->textures[3].bits_per_pixel, &game->textures[3].line_length,
			&game->textures[3].endian);
}