#include "../includes/cube3D.h"

void init_rays (t_ray *ray, t_player *player, int column)
{

	ray->camera_x = 2 * column / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x; // map_x ve map_y oyuncunun bulunduğu hücreyi gösterir
	ray->map_y = (int)player->pos_y;
	player->hit = 0;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30; // sonsuz büyük bir değer
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}


void step_and_sideDist(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

void perform_dda(t_ray *ray, t_player *player, t_map *map)
{
	while (player->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // dikey duvara çarptık
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // yatay duvara çarptık
		}
		// Çarpışma kontrolü
		if (map->map[ray->map_y][ray->map_x] == '1') // duvar hücresi
			player->hit = 1; // çarpışma gerçekleşti
	}
}

void calculate_wall_distance(t_ray *ray)
{	
	if (ray->side == 0) // dikey duvara çarptık
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else // yatay duvara çarptık
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void height_of_line_to_draw(t_ray *ray)
{
	ray->wall_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->wall_start = -ray->wall_height / 2 + SCREEN_HEIGHT / 2;
	if(ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = ray->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->wall_end >= SCREEN_HEIGHT)
		ray->wall_end = SCREEN_HEIGHT - 1;
}