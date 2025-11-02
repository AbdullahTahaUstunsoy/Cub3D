/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_double_flood.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falakus <falakus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 12:27:04 by falakus           #+#    #+#             */
/*   Updated: 2025/11/01 12:28:14 by falakus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
