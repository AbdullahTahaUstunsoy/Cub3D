/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:48:40 by austunso          #+#    #+#             */
/*   Updated: 2025/10/26 15:48:43 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void free_array(char **str)
{
	int i;

	i = 0;
	if (!str)
		return;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void free_mlx(t_game *game)
{
	if (game->mlx_content.mlx)
	{
		if (game->img.img)
			mlx_destroy_image(game->mlx_content.mlx, game->img.img);
		if (game->textures[0].img)
			mlx_destroy_image(game->mlx_content.mlx, game->textures[0].img);
		if (game->textures[1].img)
			mlx_destroy_image(game->mlx_content.mlx, game->textures[1].img);
		if (game->textures[2].img)
			mlx_destroy_image(game->mlx_content.mlx, game->textures[2].img);
		if (game->textures[3].img)
			mlx_destroy_image(game->mlx_content.mlx, game->textures[3].img);
		if (game->mlx_content.win)
			mlx_destroy_window(game->mlx_content.mlx, game->mlx_content.win);
		mlx_destroy_display(game->mlx_content.mlx);
		free(game->mlx_content.mlx);
	}
}

void free_map_contents(t_map *map)
{
	if (!map)
		return;
	if (map->fd > 2)
		close(map->fd);
	if (map->e_fd > 2)
		close(map->e_fd);
	if (map->n_fd > 2)
		close(map->n_fd);
	if (map->s_fd > 2)
		close(map->s_fd);
	if (map->w_fd > 2)
		close(map->w_fd);
	if (map->north)
		free(map->north);
	if (map->east)
		free(map->east);
	if (map->south)
		free(map->south);
	if (map->west)
		free(map->west);
	if (map->map)
		free_array(map->map);
	if (map->copy_map)
		free_array(map->copy_map);
}

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

void free_all(t_game *game)
{
	free_map_contents(game->map);
	free_mlx(game);
	free_game(game);
}