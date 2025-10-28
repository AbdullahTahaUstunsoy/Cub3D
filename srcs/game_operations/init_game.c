/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:49:08 by austunso          #+#    #+#             */
/*   Updated: 2025/10/26 16:42:10 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int set_mlx(t_game *game)
{
	t_mlx_content *mlx_content;

	mlx_content = game->mlx_content;
	mlx_content->mlx = mlx_init();
	if (!mlx_content->mlx)
	{
    	printf("Error: Failed to initialize MiniLibX (mlx_init)\n");
    	free_all(game);
		return (1);
	}
	mlx_content->win = mlx_new_window(mlx_content->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!mlx_content->win)
	{
    	printf("Error: Failed to create window (mlx_new_window)\n");
		free_all(game);
		return (1);
	}
	mlx_hook(mlx_content->win, 2, 1L<<0, press_the_key, game);
	mlx_hook(mlx_content->win, 3, 1L<<1, release_the_key, game);
	mlx_hook(mlx_content->win, 17, 0, close_the_window, game);
	mlx_loop_hook(mlx_content->win, game_loop, game);
	return (0);
}

int init_main_img(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx_content->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img.img)
	{
		printf("Error: Image could not be created!\n");
		free_all(game);
		return (1);
	}
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel, &game->img.line_length,
			&game->img.endian);
	if (!game->img.addr)
	{
		printf("Error : Image address could not be taken!\n");
		free_all(game);
		return (1);
	}
	return (0);
}

int set_game_components(t_game *game)
{
	if(set_mlx(game))
		return (1);
	if(init_main_img(game))
		return (1);
	init_keys(game);
	set_direction(game->player);
	set_player(game->player);
	set_camera_plane(game->player);
	set_player_speed(game->player);
	return (0);
}

t_game *init_structs(void)
{
	// bu structları kendi içinde başlatmalı mıyım ?
	t_game *game;
	
	game = ft_calloc(1, sizeof(t_game));
	if(!game)
		return (NULL);
	game->player = ft_calloc(1,sizeof(t_player));
	if(game->player == NULL)
		return(free_game(game));
	game->map = ft_calloc(1,sizeof(t_map));
	if(game->map == NULL)
		return(free_game(game));
	game->ray = ft_calloc(1,sizeof(t_ray));
	if(game->ray == NULL)
		return(free_game(game));
	game->mlx_content = ft_calloc(1, sizeof(t_mlx_content));
	if(game->mlx_content == NULL)
		return(free_game(game));
	return (game);
}


