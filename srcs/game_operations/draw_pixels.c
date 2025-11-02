/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falakus <falakus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:48:49 by austunso          #+#    #+#             */
/*   Updated: 2025/11/01 16:15:52 by falakus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	get_color(t_texture *img, int x, int y)
{
	return (*(size_t *)(img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8))));
}

static void	put_pixel(t_texture *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	if (!img->addr)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	determine_texture_number(t_ray *ray)
{
	if (ray->ray_calc.side == 0 && ray->ray_calc.ray_dir_x >= 0)
		ray->ray_draw.tex_num = 0;
	else if (ray->ray_calc.side == 0 && ray->ray_calc.ray_dir_x < 0)
		ray->ray_draw.tex_num = 1;
	else if (ray->ray_calc.side == 1 && ray->ray_calc.ray_dir_y > 0)
		ray->ray_draw.tex_num = 2;
	else
		ray->ray_draw.tex_num = 3;
}

static void	render_columns(t_ray *ray, int column,
							t_game *game, t_texture *texture)
{
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		if (y < ray->ray_draw.wall_start)
		{
			put_pixel(&game->img, column, y, game->map->ceiling);
		}
		else if (y < ray->ray_draw.wall_end)
		{
			ray->ray_draw.tex_y = (int)ray->ray_draw.tex_pos % 64;
			ray->ray_draw.tex_pos += ray->ray_draw.draw_step;
			ray->ray_draw.color = get_color(texture, ray->ray_draw.tex_x,
					ray->ray_draw.tex_y);
			put_pixel(&game->img, column, y, ray->ray_draw.color);
		}
		else
			put_pixel(&game->img, column, y, game->map->floor);
		y++;
	}
}

void	draw_pixels(t_ray *ray, int column, t_game *game, t_player *player)
{
	t_texture	*texture;

	if (ray->ray_calc.side == 0)
		ray->ray_draw.wall_x = player->player_pos.pos_y
			+ ray->ray_calc.perp_wall_dist * ray->ray_calc.ray_dir_y;
	else
		ray->ray_draw.wall_x = player->player_pos.pos_x
			+ ray->ray_calc.perp_wall_dist * ray->ray_calc.ray_dir_x;
	determine_texture_number(ray);
	ray->ray_draw.wall_x -= floor(ray->ray_draw.wall_x);
	ray->ray_draw.tex_x = (int)(ray->ray_draw.wall_x * 64.0);
	if ((ray->ray_calc.ray_dir_x < 0 && ray->ray_calc.side == 0)
		|| (ray->ray_calc.ray_dir_y > 0 && ray->ray_calc.side == 1))
		ray->ray_draw.tex_x = 64 - ray->ray_draw.tex_x - 1;
	ray->ray_draw.draw_step = 1.0 * 64 / ray->ray_draw.wall_height;
	ray->ray_draw.tex_pos = (ray->ray_draw.wall_start - SCREEN_HEIGHT / 2
			+ ray->ray_draw.wall_height / 2)
		* ray->ray_draw.draw_step;
	texture = &game->textures[ray->ray_draw.tex_num];
	render_columns(ray, column, game, texture);
}
