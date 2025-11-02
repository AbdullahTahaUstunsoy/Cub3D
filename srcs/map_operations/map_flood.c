/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_flood.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falakus <falakus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:58:22 by falakus           #+#    #+#             */
/*   Updated: 2025/11/01 17:15:52 by falakus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	is_invalid(t_map *map, int x, int y)
{
	if (!map->copy_map[y][x + 1] || map->copy_map[y][x + 1] == ' '
		|| map->copy_map[y][x + 1] == '*')
		return (1);
	if (x - 1 < 0 || map->copy_map[y][x - 1] == ' '
		|| map->copy_map[y][x - 1] == '*')
		return (1);
	if (!map->copy_map[y + 1] || !map->copy_map[y + 1][x]
		|| map->copy_map[y + 1][x] == ' ' || map->copy_map[y + 1][x] == '*')
		return (1);
	if (y - 1 < 0 || map->copy_map[y - 1][x] == ' '
		|| map->copy_map[y - 1][x] == '*')
		return (1);
	return (0);
}

int	flood_check(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->copy_map[y])
	{
		x = 0;
		while (map->copy_map[y][x])
		{
			if (map->copy_map[y][x] == 'F')
			{
				if (is_invalid(map, x, y))
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	fill_all_map(t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (map->copy_map[y])
	{
		x = 0;
		while (map->copy_map[y][x])
		{
			c = map->copy_map[y][x];
			if (c == '0' || c == 'S' || c == 'W' || c == 'E' || c == 'N')
				map->copy_map[y][x] = 'F';
			x++;
		}
		y++;
	}
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
	if (map->player->player_pos.pos_x == -1.0
		|| map->player->player_pos.pos_y == -1.0)
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
