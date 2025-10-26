/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 17:00:04 by falakus           #+#    #+#             */
/*   Updated: 2025/10/26 15:43:08 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int check_map_name(char *str)
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
	game->map->player = game->player;
	game->map->player->pos_x = -1.0;
	game->map->player->pos_y = -1.0;
}

int	double_map_check(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map->copy_map[i])
	{
		j = 0;
		while (map->copy_map[i][j])
		{
			if (map->copy_map[i][j] == '1' || map->copy_map[i][j] == '0')
			{
				printf("Double map error!!!\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	find_start_position(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map->copy_map[y])
	{
		x = 0;
		while (map->copy_map[y][x])
		{
			if (map->copy_map[y][x] == '1')
			{
				map->start_x = x;
				map->start_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	double_map_flood(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || y >= map->map_height)
		return ;
	if (map->copy_map[y][x] == '*' || map->copy_map[y][x] == 'T'
		|| map->copy_map[y][x] == '\0' || map->copy_map[y][x] == '\n')
		return ;
	map->copy_map[y][x] = 'T';
	double_map_flood(map, x + 1, y);
	double_map_flood(map, x - 1, y);
	double_map_flood(map, x, y + 1);
	double_map_flood(map, x, y - 1);
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
	flood_fill(map, map->player->pos_x, map->player->pos_y, '0');
	if (flood_check(map, map->player->pos_x, map->player->pos_y))
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
