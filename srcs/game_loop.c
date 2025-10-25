#include "../includes/cube3D.h"

void raycast(t_ray *ray, t_player *player, t_game *game)
{
	int column;

	column = 0;
	while (column < SCREEN_WIDTH)
	{
		init_rays(ray, player, column);
		step_and_sideDist(ray, player);
		perform_dda(ray, player, game->map);
		calculate_wall_distance(ray);
		height_of_line_to_draw(ray);
		draw_pixels(ray, column, game); //textured kısmı başladı.
		//birkaç fonksiyon daha eklememiz gerekebilir.
		column++;
	}
}

void render(t_game *game)
{
    raycast(game->ray, game->player, game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
}

int game_loop (t_game *game)
{
	move(game);
	render(game); //hareket edemiyorusa return 0 olup ne olacak ?
	return 0;
}




