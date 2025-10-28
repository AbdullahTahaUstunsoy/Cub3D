/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_engine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:49:22 by austunso          #+#    #+#             */
/*   Updated: 2025/10/26 17:56:17 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void init_rays (t_ray *ray, t_player *player, int column)
{
	ray->ray_calc.camera_x = 2 * column / (double)SCREEN_WIDTH - 1;
	ray->ray_calc.ray_dir_x = player->player_pos.dir_x + player->player_pos.plane_x * ray->ray_calc.camera_x;
	ray->ray_calc.ray_dir_y = player->player_pos.dir_y + player->player_pos.plane_y * ray->ray_calc.camera_x;
	ray->ray_calc.map_x = (int)player->player_pos.pos_x;
	ray->ray_calc.map_y = (int)player->player_pos.pos_y;
	ray->ray_calc.hit = 0;
	if (ray->ray_calc.ray_dir_x == 0)
		ray->ray_calc.delta_dist_x = 1e30;
	else
		ray->ray_calc.delta_dist_x = fabs(1 / ray->ray_calc.ray_dir_x);
	if (ray->ray_calc.ray_dir_y == 0)
		ray->ray_calc.delta_dist_y = 1e30;
	else
		ray->ray_calc.delta_dist_y = fabs(1 / ray->ray_calc.ray_dir_y);
}


void step_and_sideDist(t_ray *ray, t_player *player)
{
	if (ray->ray_calc.ray_dir_x < 0)
	{
		ray->ray_calc.step_x = -1;
		ray->ray_calc.side_dist_x = (player->player_pos.pos_x - ray->ray_calc.map_x) * ray->ray_calc.delta_dist_x;
	}
	else
	{
		ray->ray_calc.step_x = 1;
		ray->ray_calc.side_dist_x = (ray->ray_calc.map_x + 1.0 - player->player_pos.pos_x) * ray->ray_calc.delta_dist_x;
	}
	if (ray->ray_calc.ray_dir_y < 0)
	{
		ray->ray_calc.step_y = -1;
		ray->ray_calc.side_dist_y = (player->player_pos.pos_y - ray->ray_calc.map_y) * ray->ray_calc.delta_dist_y;
	}
	else
	{
		ray->ray_calc.step_y = 1;
		ray->ray_calc.side_dist_y = (ray->ray_calc.map_y + 1.0 - player->player_pos.pos_y) * ray->ray_calc.delta_dist_y;
	}
}

void perform_dda(t_ray *ray, t_map *map)
{
	while (ray->ray_calc.hit == 0)
	{
		if (ray->ray_calc.side_dist_x < ray->ray_calc.side_dist_y)
		{
			ray->ray_calc.side_dist_x += ray->ray_calc.delta_dist_x;
			ray->ray_calc.map_x += ray->ray_calc.step_x;
			ray->ray_calc.side = 0;
		}
		else
		{
			ray->ray_calc.side_dist_y += ray->ray_calc.delta_dist_y;
			ray->ray_calc.map_y += ray->ray_calc.step_y;
			ray->ray_calc.side = 1;
		}
		if (map->map[ray->ray_calc.map_y][ray->ray_calc.map_x] == '1')
			ray->ray_calc.hit = 1;
	}
}

void calculate_wall_distance(t_ray *ray)
{	
	if (ray->ray_calc.side == 0)
		ray->ray_calc.perp_wall_dist = (ray->ray_calc.side_dist_x - ray->ray_calc.delta_dist_x);
	else
		ray->ray_calc.perp_wall_dist = (ray->ray_calc.side_dist_y - ray->ray_calc.delta_dist_y);
}

void height_of_line_to_draw(t_ray *ray)
{
	ray->ray_draw.wall_height = (int)(SCREEN_HEIGHT / ray->ray_calc.perp_wall_dist);
	ray->ray_draw.wall_start = -ray->ray_draw.wall_height / 2 + SCREEN_HEIGHT / 2;
	if(ray->ray_draw.wall_start < 0)
		ray->ray_draw.wall_start = 0;
	ray->ray_draw.wall_end = ray->ray_draw.wall_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->ray_draw.wall_end >= SCREEN_HEIGHT)
		ray->ray_draw.wall_end = SCREEN_HEIGHT - 1;
}