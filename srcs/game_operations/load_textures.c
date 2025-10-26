/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:50:01 by austunso          #+#    #+#             */
/*   Updated: 2025/10/26 15:50:03 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void load_textures(t_game *game)
{
	//NULL kontrollerini ekle
	game->textures[NORTH].img = mlx_xpm_file_to_image(game->mlx, game->map->north,
			&game->textures[NORTH].width, &game->textures[NORTH].height);
	game->textures[NORTH].addr = mlx_get_data_addr(game->textures[NORTH].img,
			&game->textures[NORTH].bits_per_pixel, &game->textures[NORTH].line_length,
			&game->textures[NORTH].endian);
	game->textures[SOUTH].img = mlx_xpm_file_to_image(game->mlx, game->map->south,
			&game->textures[SOUTH].width, &game->textures[SOUTH].height);
	game->textures[SOUTH].addr = mlx_get_data_addr(game->textures[SOUTH].img,
			&game->textures[SOUTH].bits_per_pixel, &game->textures[SOUTH].line_length,
			&game->textures[SOUTH].endian);
	game->textures[WEST].img = mlx_xpm_file_to_image(game->mlx, game->map->west,
			&game->textures[WEST].width, &game->textures[WEST].height);
	game->textures[WEST].addr = mlx_get_data_addr(game->textures[WEST].img,
			&game->textures[WEST].bits_per_pixel, &game->textures[WEST].line_length,
			&game->textures[WEST].endian);
	game->textures[EAST].img = mlx_xpm_file_to_image(game->mlx, game->map->east,
			&game->textures[EAST].width, &game->textures[EAST].height);
	game->textures[EAST].addr = mlx_get_data_addr(game->textures[EAST].img,
			&game->textures[EAST].bits_per_pixel, &game->textures[EAST].line_length,
			&game->textures[EAST].endian);
}
