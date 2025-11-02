/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falakus <falakus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:41:51 by falakus           #+#    #+#             */
/*   Updated: 2025/11/01 12:38:32 by falakus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_files(t_map *map)
{
	int	flag;

	flag = 0;
	if (check_files_names(map))
		flag = 2;
	map->e_fd = open(map->east, O_RDONLY);
	map->s_fd = open(map->south, O_RDONLY);
	map->n_fd = open(map->north, O_RDONLY);
	map->w_fd = open(map->west, O_RDONLY);
	if (map->e_fd == -1 || map->w_fd == -1 || map->n_fd == -1
		|| map->s_fd == -1)
		flag = 1;
	if (flag == 1)
	{
		printf("Can't open textures files!\n");
		return (1);
	}
	else if (flag == 2)
	{
		printf("Wrong texture file name!\n");
		return (1);
	}
	return (0);
}

int	check_files_names(t_map *map)
{
	int	len;

	len = ft_strlen(map->east);
	if (map->east[len - 1] != 'm' && map->east[len - 2] != 'p'
		&& map->east[len - 3] != 'x' && map->east[len - 4] != '.')
		return (1);
	len = ft_strlen(map->west);
	if (map->west[len - 1] != 'm' && map->west[len - 2] != 'p'
		&& map->west[len - 3] != 'x' && map->west[len - 4] != '.')
		return (1);
	len = ft_strlen(map->south);
	if (map->south[len - 1] != 'm' && map->south[len - 2] != 'p'
		&& map->south[len - 3] != 'x' && map->south[len - 4] != '.')
		return (1);
	len = ft_strlen(map->north);
	if (map->north[len - 1] != 'm' && map->north[len - 2] != 'p'
		&& map->north[len - 3] != 'x' && map->north[len - 4] != '.')
		return (1);
	return (0);
}

int	check_map_elements(t_map *map)
{
	char	*line;
	char	*trim;

	map->map = malloc(sizeof(char *));
	if (!map->map)
		return (1);
	map->map[0] = NULL;
	line = get_next_line(map->fd);
	while (line)
	{
		trim = adjust_line(map, line, map->count);
		if (trim == NULL)
		{
			line = get_next_line(map->fd);
			continue ;
		}
		if (map_elements(map, trim, line, ++map->count))
			return (free(line), free(trim), get_next_line(-1), 1);
		line = get_next_line(map->fd);
	}
	if (map->map_size == 0)
		return (printf("Missing map!!!\n"), 1);
	if (map->count == 0 && !line)
		return (printf("Map is empty!!!\n"), 1);
	return (0);
}

char	*adjust_line(t_map *map, char *line, int count)
{
	char	*trimmed_line;

	if (check_tab(line))
		map->flag = 1;
	if (count < 6)
		trimmed_line = ft_strtrim(line, "\n");
	else
	{
		if (line[0] == '\n')
			trimmed_line = ft_strdup("\n");
		else
			trimmed_line = ft_strtrim(line, "\n");
	}
	if ((trimmed_line[0] == '\0' || (trimmed_line[0] == '\n' && count < 6)))
	{
		free(line);
		free(trimmed_line);
		return (NULL);
	}
	return (trimmed_line);
}

int	map_elements(t_map *map, char *trimmed_line, char *line, int count)
{
	if (count < 7)
	{
		if (check_identifiers(map, trimmed_line))
			return (1);
	}
	else
	{
		if (check_invalid_map_line(trimmed_line))
			return (1);
		if (map_fill(map, trimmed_line, map->map_size))
			return (1);
		map->map_size++;
	}
	free(line);
	free(trimmed_line);
	return (0);
}
