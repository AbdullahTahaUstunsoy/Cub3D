/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:50:01 by austunso          #+#    #+#             */
/*   Updated: 2025/10/26 17:49:38 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int load_textures_north(t_game * game)
{
	game->textures[NORTH].img = mlx_xpm_file_to_image(game->mlx_content->mlx, game->map->north,
			&game->textures[NORTH].width, &game->textures[NORTH].height);
	if (!game->textures[NORTH].img)
	{
		printf("Error: Failed to load north texture\n");
		free_all(game);
		return (1);
	}
	game->textures[NORTH].addr = mlx_get_data_addr(game->textures[NORTH].img,
			&game->textures[NORTH].bits_per_pixel, &game->textures[NORTH].line_length,
			&game->textures[NORTH].endian);
	if (!game->textures[NORTH].addr)
	{
		printf("Error: Failed to get north texture address\n");
		free_all(game);
		return (1);
	}
	return (0);
}

static int load_textures_south(t_game *game)
{
	game->textures[SOUTH].img = mlx_xpm_file_to_image(game->mlx_content->mlx, game->map->south,
			&game->textures[SOUTH].width, &game->textures[SOUTH].height);
	if (!game->textures[SOUTH].img)
	{
		printf("Error: Failed to load south texture\n");
		free_all(game);
		return (1);
	}
	game->textures[SOUTH].addr = mlx_get_data_addr(game->textures[SOUTH].img,
			&game->textures[SOUTH].bits_per_pixel, &game->textures[SOUTH].line_length,
			&game->textures[SOUTH].endian);
	if (!game->textures[SOUTH].addr)
	{
		printf("Error: Failed to get south texture address\n");
		free_all(game);
		return (1);
	}
	return (0);
}


static int load_textures_west(t_game *game)
{
	game->textures[WEST].img = mlx_xpm_file_to_image(game->mlx_content->mlx, game->map->west,
			&game->textures[WEST].width, &game->textures[WEST].height);
	if(!game->textures[WEST].img)
	{
		printf("Error: Failed to load west texture\n");
		free_all(game);
		return (1);
	}
	game->textures[WEST].addr = mlx_get_data_addr(game->textures[WEST].img,
			&game->textures[WEST].bits_per_pixel, &game->textures[WEST].line_length,
			&game->textures[WEST].endian);
	if(!game->textures[WEST].addr)
	{
		printf("Error: Failed to get west texture address\n");
		free_all(game);
		return (1);
	}
	return (0);
}

static int load_textures_east(t_game *game)
{
	game->textures[EAST].img = mlx_xpm_file_to_image(game->mlx_content->mlx, game->map->east,
			&game->textures[EAST].width, &game->textures[EAST].height);
	if(!game->textures[EAST].img)
	{
		printf("Error: Failed to load east texture\n");
		free_all(game);
		return (1);
	}
	game->textures[EAST].addr = mlx_get_data_addr(game->textures[EAST].img,
			&game->textures[EAST].bits_per_pixel, &game->textures[EAST].line_length,
			&game->textures[EAST].endian);
	if (!game->textures[EAST].addr)
	{
		printf("Error: Failed to get east texture address\n");
		free_all(game);
		return (1);
	}
	return (0);
}

int load_textures(t_game *game)
{
	if (load_textures_north(game))
		return (1);
	if (load_textures_south(game))
		return (1);
	if (load_textures_west(game))
		return (1);
	if (load_textures_east(game))
		return (1);
	return (0);
}
