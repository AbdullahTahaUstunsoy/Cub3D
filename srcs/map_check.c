/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falakus <falakus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 16:52:03 by falakus           #+#    #+#             */
/*   Updated: 2025/10/25 19:34:39 by falakus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	check_invalid_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W' && line[i] != '\n')
		{
			printf("Invalid character in map!!!\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_isvalid(char *str)
{
	int		i;
	int		j;
	char	*number;

	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		if (str[i] != ' ' && (str[i] < '0' || str[i] > '9') && str[i] != '\n')
			return (-1);
		if (str[i] >= '0' && str[i] <= '9')
			j++;
	}
	number = malloc((sizeof(char) * j) + 1);
	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		if (str[i] != ' ')
			number[j++] = str[i];
	}
	number[j] = '\0';
	i = ft_atoi(number);
	free(number);
	return (i);
}

int	check_coloring(char *line)
{
	int		r;
	int		g;
	int		b;
	char	**numbers;

	if (!line)
		return (-2);
	numbers = ft_split(line, ',');
	free(line);
	if (!numbers)
		return (-2);
	if (!numbers[0] || !numbers[1] || !numbers[2] || numbers[3] != NULL)
	{
		free_array(numbers);
		return (-2);
	}
	r = ft_isvalid(numbers[0]);
	g = ft_isvalid(numbers[1]);
	b = ft_isvalid(numbers[2]);
	free_array(numbers);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-2);
	return ((r << 16) | (g << 8) | b);
}

int	check_identifiers(t_map *map, char *identifier)
{
	char	*line;

	line = ft_strtrim(identifier, " ");
	if (!line)
		return (1);
	if (!ft_strncmp(line, "NO ", 3))
		map->north = ft_strtrim(line + 3, " ");
	else if (!ft_strncmp(line, "SO ", 3))
		map->south = ft_strtrim(line + 3, " ");
	else if (!ft_strncmp(line, "WE ", 3))
		map->west = ft_strtrim(line + 3, " ");
	else if (!ft_strncmp(line, "EA ", 3))
		map->east = ft_strtrim(line + 3, " ");
	else if (!ft_strncmp(line, "F ", 2))
		map->floor = check_coloring(ft_strtrim(line + 2, " "));
	else if (!ft_strncmp(line, "C ", 2))
		map->ceiling = check_coloring(ft_strtrim(line + 2, " "));
	else
		return (free(line), printf("Wrong map identifier\n"), 1);
	if (map->floor == -2 || map->ceiling == -2)
		return (free(line), printf("Wrong color input!\n"), 1);
	free(line);
	return (0);
}

int	check_tab(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			flag = 1;
		i++;
	}
	return (flag);
}
