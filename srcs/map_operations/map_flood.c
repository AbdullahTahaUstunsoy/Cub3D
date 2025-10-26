/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:58:22 by falakus           #+#    #+#             */
/*   Updated: 2025/10/26 15:43:05 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	flood_check(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || !map->copy_map[y] || !map->copy_map[y][x])
		return (1);
	if (map->copy_map[y][x] == '*' || map->copy_map[y][x] == '0')
		return (1);
	if (map->copy_map[y][x] != 'F')
		return (0);
	map->copy_map[y][x] = 'V';
	if (flood_check(map, x + 1, y))
		return (1);
	if (flood_check(map, x - 1, y))
		return (1);
	if (flood_check(map, x, y + 1))
		return (1);
	if (flood_check(map, x, y - 1))
		return (1);
	return (0);
}

void	flood_fill(t_map *map, int x, int y, char target)
{
	char	fill;

	fill = 'F';
	if (x < 0 || y < 0 || !map->copy_map[y] || !map->copy_map[y][x])
		return ;
	if (map->copy_map[y][x] != target)
		return ;
	map->copy_map[y][x] = fill;
	flood_fill(map, x + 1, y, target);
	flood_fill(map, x - 1, y, target);
	flood_fill(map, x, y + 1, target);
	flood_fill(map, x, y - 1, target);
}

int	fill_player_struct(int x, int y, int flag, t_map *map)
{
	if (!flag)
	{
		map->player->pos_x = (double)x;
		map->player->pos_y = (double)y;
		map->player->player_dir = map->copy_map[y][x];
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

int	find_player_position(t_map *map)
{
	int	y;
	int	x;
	int	flag;

	y = -1;
	x = -1;
	flag = 0;
	while (map->copy_map[++y] != NULL)
	{
		x = 0;
		while (map->copy_map[y][++x] != '\0')
		{
			if (map->copy_map[y][x] == 'W' || map->copy_map[y][x] == 'E'
				|| map->copy_map[y][x] == 'N' || map->copy_map[y][x] == 'S')
			{
				if (fill_player_struct(x, y, flag, map))
					return (1);
				flag = 1;
			}
		}
	}
	if (map->player->pos_x == -1.0 || map->player->pos_y == -1.0)
		return (printf("There isn't any player!!!\n"), 1);
	return (0);
}

int	find_longest_line(t_map *map)
{
	int	i;
	int	length;
	int	tmp;

	i = 0;
	length = 0;
	while (map->map[i] != NULL)
	{
		tmp = ft_strlen(map->map[i]);
		if (tmp > length)
			length = tmp;
		i++;
	}
	return (length);
}
