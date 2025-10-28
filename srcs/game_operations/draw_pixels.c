/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:48:49 by austunso          #+#    #+#             */
/*   Updated: 2025/10/26 17:56:54 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_color(t_texture *img, int x, int y)
{
	return (*(size_t *)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8))));
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


void determine_texture_number(t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x >= 0)
		ray->tex_num = 0;
	else if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_num = 1;
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex_num = 2;
	else
		ray->tex_num = 3;
}

static void render_columns(t_ray *ray, int column, t_game *game, t_texture *texture)
{
	int y;

	y = 0;
	while (y < SCREEN_HEIGHT)
    {
        if (y < ray->wall_start)
        {
            put_pixel(&game->img, column, y, game->map->ceiling);
        }
        else if (y < ray->wall_end)
        {
            ray->tex_y = (int)ray->tex_pos % 64;
            ray->tex_pos += ray->draw_step;
            ray->color = get_color(texture, ray->tex_x, ray->tex_y);
            put_pixel(&game->img, column, y, ray->color);
        }
        else
            put_pixel(&game->img, column, y, game->map->floor);
        y++;
    }
}

void draw_pixels(t_ray *ray, int column, t_game *game, t_player *player)
{
    t_texture *texture;
    
    if (ray->side == 0)
        ray->wall_x = player->player_pos.pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else 
        ray->wall_x = player->player_pos.pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    
    determine_texture_number(ray);
    ray->wall_x -= floor(ray->wall_x);    
    ray->tex_x = (int)(ray->wall_x * 64.0); 

    if ((ray->ray_dir_x < 0 && ray->side == 0) || (ray->ray_dir_y > 0 && ray->side == 1))
        ray->tex_x = 64 - ray->tex_x - 1;

    ray->draw_step = 1.0 * 64 / ray->wall_height; 
    
    ray->tex_pos = (ray->wall_start - SCREEN_HEIGHT / 2 + ray->wall_height / 2) * ray->draw_step;

    texture = &game->textures[ray->tex_num];
    render_columns(ray, column, game, texture);
}




/*
void draw_pixels(t_ray *ray, int column, t_game *game)
{
    int y;
    t_texture *texture;
    
    if (ray->side == 0)
        ray->wall_x = game->player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else 
        ray->wall_x = game->player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
    
    determine_texture_number(ray);
    ray->wall_x -= floor(ray->wall_x);
    
    // (int) cast'i zorunlu
    ray->tex_x = (int)(ray->wall_x * 64.0); 

    if ((ray->ray_dir_x < 0 && ray->side == 0) || (ray->ray_dir_y > 0 && ray->side == 1))
        ray->tex_x = 64 - ray->tex_x - 1;

    // 1.0 * ... ondalıklı bölme için zorunlu
    ray->draw_step = 1.0 * 64 / ray->wall_height; 
    
    ray->tex_pos = (ray->wall_start - SCREEN_HEIGHT / 2 + ray->wall_height / 2) * ray->draw_step;

    texture = &game->textures[ray->tex_num];

    // 'for' yerine standart 'while' döngüsü
    y = 0;
    while (y < SCREEN_HEIGHT)
    {
        if (y < ray->wall_start)
        {
            put_pixel(&game->img, column, y, game->map->ceiling);
        }
        // EN ÖNEMLİ DÜZELTME: (size_t) cast'i kaldırıldı.
        // int y < double ray->wall_end karşılaştırması doğrudur.
        else if (y < ray->wall_end) 
        {
            // (int) cast'i '%' (mod) operatörü için ZORUNLUDUR.
            ray->tex_y = (int)ray->tex_pos % 64;
            ray->tex_pos += ray->draw_step;
            ray->color = get_color(texture, ray->tex_x, ray->tex_y);
            put_pixel(&game->img, column, y, ray->color);
        }
        else
        {
            put_pixel(&game->img, column, y, game->map->floor);
        }
        
        // Döngü değişkenini sonda artır
        y++;
    }
}
*/