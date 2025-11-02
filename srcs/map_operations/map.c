/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falakus <falakus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:00:04 by falakus           #+#    #+#             */
/*   Updated: 2025/11/01 17:15:49 by falakus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	fill_player_struct(int x, int y, int flag, t_map *map)
{
	if (!flag)
	{
		map->player->player_pos.pos_x = (double)x;
		map->player->player_pos.pos_y = (double)y;
		map->player->player_pos.player_dir = map->copy_map[y][x];
		map->map[y][x] = '0';
		map->copy_map[y][x] = '0';
	}
	else
	{
		printf("Can't be more than one player!!!\n");
		return (1);
	}
	return (0);
}

int	check_map_name(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = ft_strlen(str);
	if (str[i - 1] != 'b')
		flag = 1;
	else if (str[i - 2] != 'u')
		flag = 1;
	else if (str[i - 3] != 'c')
		flag = 1;
	else if (str[i - 4] != '.')
		flag = 1;
	else if (str[i - 5] == '/')
		flag = 1;
	if (flag == 1)
		printf("Wrong file name!\n");
	return (flag);
}

void	map_init(t_game *game)
{
	game->map->fd = -2;
	game->map->start_x = -1;
	game->map->start_y = -1;
	game->map->e_fd = -2;
	game->map->s_fd = -2;
	game->map->n_fd = -2;
	game->map->w_fd = -2;
	game->map->map_height = 0;
	game->map->ceiling = -1;
	game->map->floor = -1;
	game->map->north = NULL;
	game->map->south = NULL;
	game->map->east = NULL;
	game->map->west = NULL;
	game->map->map_size = 0;
	game->map->count = 0;
	game->map->player = game->player;
	game->player->player_pos.pos_x = -1.0;
	game->player->player_pos.pos_y = -1.0;
}

int	fill_map_struct(char *map_file, t_map *map)
{
	map->fd = open(map_file, O_RDONLY);
	if (map->fd == -1)
		return (printf("Can't open the map file!\n"), 1);
	if (check_map_elements(map) || check_files(map))
		return (1);
	map->copy_map = copy_map(map);
	if (!map->copy_map || map_control(map) || find_player_position(map))
		return (1);
	fill_all_map(map);
	if (flood_check(map))
		return (printf("Map is not closed!!!\n"), 1);
	find_start_position(map);
	double_map_flood(map, map->start_x, map->start_y);
	if (double_map_check(map))
		return (1);
	return (0);
}

int	map_operations(t_game *game, char **av)
{
	map_init(game);
	if (check_map_name(av[1]))
	{
		free_all(game);
		return (1);
	}
	if (fill_map_struct(av[1], game->map))
	{
		free_all(game);
		return (1);
	}
	return (0);
}
