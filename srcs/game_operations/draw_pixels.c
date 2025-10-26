/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:48:49 by austunso          #+#    #+#             */
/*   Updated: 2025/10/26 15:48:52 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_color(t_texture *img, int x, int y)
{
	return (*(size_t *)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)))); //Texture'dan alınan rengi belirler.
}

static void	put_pixel(t_texture *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) //Eğer pixel ekrandan dışarıda kalıyorsa fonksiyonu sonlandırırız.
		return ;
	if (!img->addr)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)); //Koyduğumuz pixelin tam ve kesin adresini belirler(Adresin başlangıcı + (y * satır uzunluğu + x * pixelin bit uzunluğu / 8)) -> (satır uzunluğu = ekran genişliği * 4)
	*(unsigned int *)dst = color; //Bu adresin içine color değerini atarız.
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

void draw_pixels(t_ray *ray, int column, t_game *game)
{
	// ray->wall_x'i hesapla (duvarın tam olarak neresine çarptık?)
    if (ray->side == 0) // Dikey duvar
		ray->wall_x = game->player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else // Yatay duvar
		ray->wall_x = game->player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	determine_texture_number(ray);
	ray->wall_x -= floor(ray->wall_x); //Texture'ın hangi konumda başlayacağını belirler. (Örneğin 3.5 bir duvara çarptıysak texture 0.5 konumunda başlayacak. Duvarı 1'e 1'lik bir texutre ile kaplarsak 0.5'ten başlayarak 1'e kadar olan kısmı duvara çizeriz. Çünkü diğer türlü texture yanlış çizilir.)
	ray->tex_x = (int)(ray->wall_x * (double)64); //Texture 64x64 olduğu için başlangıç pixelini 64 ile çarparız. Bu sayede textureda doğru konumundan çizmeye başlarız.
	if ((ray->ray_dir_x < 0 && ray->side == 0) || (ray->ray_dir_y > 0 && ray->side == 1)) //Eğer duvar x ekseninde bir duvar ise ve rayin x yönündeki hareketi pozitifse dokuyu tersten çizmemiz gerekir.
		ray->tex_x = 64 - ray->tex_x - 1; //Bu yüzden texture'ı tersten çizmek için texture'ın başlangıç pixelini 64'ten çıkarırız.
	ray->draw_step = 1.0 * 64 / ray->wall_height; //Duvarın yüksekliğine göre texture'ın çizilme adımını belirler. (Duvar büyükse pixelleri daha büyük çizmemiz gerekir, küçükse daha küçük çizmemiz gerekir.)
	ray->tex_pos = (ray->wall_start - SCREEN_HEIGHT / 2 + ray->wall_height / 2) * ray->draw_step;
	size_t y;
	t_texture *tmp;

	tmp = &game->textures[ray->tex_num]; //Hangi texture'ı kullanacağımızı belirler.
	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		if (y < ray->wall_start)
			put_pixel(&game->img, column, y, game->map->ceiling);
		else if (y < (size_t)ray->wall_end)
		{
			ray->tex_y = (int)ray->tex_pos % 64; //Texture'ın 0-63 sınırları arasında kalmasını sağlar. (Texture 64x64 olduğu için 64'e modunu alırız)
			ray->tex_pos += ray->draw_step; //Çizgi uzunluğuna göre hesapladığımız step kadar texture'ın pozisyonunu güncelleriz.
			ray->color = get_color(tmp, ray->tex_x, ray->tex_y); //Texture'dan alınan rengi belirler.
			put_pixel(&game->img, column, y, ray->color); //Texture'dan alınan rengi çizer.
		}
		else
			put_pixel(&game->img, column, y, game->map->floor);
	}
}