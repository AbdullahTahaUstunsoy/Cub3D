/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:53:31 by falakus           #+#    #+#             */
/*   Updated: 2025/10/26 15:43:03 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	character_check(t_map *map)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	flag = 0;
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
				&& map->map[i][j] != ' ')
				if (map->map[i][j] != 'N' && map->map[i][j] != 'S'
					&& map->map[i][j] != 'E' && map->map[i][j] != 'W'
					&& map->map[i][j] != '\n')
					flag = 1;
			j++;
		}
		i++;
	}
	if (flag)
		return (printf("Invalid character in map !!\n"), 1);
	return (0);
}

int	format_line(char **line, int len)
{
	int		j;
	int		tmp;
	char	*new;

	tmp = ft_strlen(*line);
	new = malloc(len + 1);
	if (!new)
		return (1);
	ft_memcpy(new, *line, tmp);
	j = -1;
	while (++j < tmp)
		if (new[j] == ' ')
			new[j] = '*';
	while (tmp < len)
		new[tmp++] = '*';
	new[len] = '\0';
	free(*line);
	*line = new;
	return (0);
}

int	map_control(t_map *map)
{
	int	i;
	int	len;

	len = find_longest_line(map);
	if (len < 3 || map->map_height < 3)
		return (printf("Map is too small!!!\n"), 1);
	i = -1;
	while (map->copy_map[++i])
		if (format_line(&map->copy_map[i], len))
			return (1);
	return (0);
}

char	**copy_map(t_map *map)
{
	char	**copy;
	int		i;

	copy = malloc((map->map_height + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->map_height)
	{
		copy[i] = ft_strdup(map->map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	if (character_check(map))
		return (NULL);
	return (copy);
}

int	map_fill(t_map *map, char *line, int map_size)
{
	int		i;
	char	**new_map;

	i = 0;
	new_map = malloc((map_size + 2) * sizeof(char *));
	if (!new_map)
		return (1);
	while (i < map_size)
	{
		new_map[i] = map->map[i];
		i++;
	}
	new_map[map_size] = ft_strdup(line);
	new_map[map_size + 1] = NULL;
	free(map->map);
	map->map = new_map;
	map->map_height++;
	return (0);
}
