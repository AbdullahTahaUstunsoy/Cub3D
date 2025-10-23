#include "../includes/cube3D.h"

int double_map_check(t_map *map)
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

void double_map_flood(t_map *map, int x, int y)

{
    if (x < 0 || y < 0 || y >= map->map_height)
        return;

    if (map->copy_map[y][x] == '*' || map->copy_map[y][x] == 'T' || map->copy_map[y][x] == '\0' || map->copy_map[y][x] == '\n')
        return;

    map->copy_map[y][x] = 'T';

    double_map_flood(map, x + 1, y);
    double_map_flood(map, x - 1, y);
    double_map_flood(map, x, y + 1);
    double_map_flood(map, x, y - 1);

}

int check_invalid_map_line(char *line)
{
    int i;

	i = 0;
    while (line[i])
    {
        if (line[i] != '0' && line[i] != '1' && line[i] != ' ' &&
            line[i] != 'N' && line[i] != 'S' &&
            line[i] != 'E' && line[i] != 'W' && line[i] != '\n')
        {
            printf("Invalid character in map %c line %d!!!\n", line[i], i);
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
		if (str[i] != ' ' && (str[i] < '0' || str[i] > '9') && str[i] != '\n') // yinr r den oluyor
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

int check_coloring(char *line)
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
	if (ft_strncmp(line, "NO ", 3) == 0)
		map->north = ft_strtrim(line, "NO ");
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->south = ft_strtrim(line, "SO ");
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->west = ft_strtrim(line, "WE ");
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->east = ft_strtrim(line, "EA ");
	else if (ft_strncmp(line, "F ", 2) == 0)
		map->floor = check_coloring(ft_strtrim((line + 1), " "));
	else if (ft_strncmp(line, "C ", 2) == 0)
		map->ceiling = check_coloring(ft_strtrim((line + 1), " "));
	else
	{
		printf("Wrong map identifier\n");
		free(line);
		return (1);
	}
	if (map->floor == -2 || map->ceiling == -2)
	{
		free(line);
		printf("Wrong color input!\n");
		return (1);
	}
	free(line);
	return (0);
}

int check_tab(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while(str[i])
	{
		if (str[i] == '\t')
			flag = 1;
		i++;
	}
	return (flag);
}

int check_map_elements(t_map *map)
{
	int		count;
	char	*line;
	char	*trimmed_line;
	int		map_size;
	int		r_flag;

	r_flag = 0;
	map_size = 0;
	count = 0;
	map->map = malloc(sizeof(char *));
	if (!map->map)
		return (1);
	/* start with empty, NULL-terminated map array */
	map->map[0] = NULL;
	while ((line = get_next_line(map->fd)))
	{
		if (check_tab(line))
			map->flag = 1;
		if (count < 7)
			trimmed_line = ft_strtrim(line, "\n");
		else
		{
			if (line[0] == '\n')
				trimmed_line = ft_strdup(" \n");
			else
			{
				trimmed_line = ft_strtrim(line, "\n");
			}
			//free(line);
		}
		if (trimmed_line[0] == '\0' || trimmed_line[0] == '\n')
		{
			free(line);
			free(trimmed_line);
			continue;
		}
		count++;
		if (count < 7)
		{
			if (check_identifiers(map, trimmed_line))
			{
				r_flag = 1;
				break;
			}
		}
/* 		else if (check_map_lines(trimmed_line))
			return(1); */
		else 
		{
			if (check_invalid_map_line(trimmed_line))
			{
				r_flag = 1;
				break;
			}
			if (map_fill(map, trimmed_line, map_size))
			{
				r_flag = 1;
				break;
			}
			map_size++;
		}
		free(line);
		free(trimmed_line);
	}
	if (r_flag)
	{
		free(line);
		free(trimmed_line);
		get_next_line(-1);
		return (1);
	}
	if (map_size == 0)
	{
		printf("Missing map!!!\n");
		return (1);
	}
	if (count == 0 && line == NULL)
	{
		printf("Map is empty!!!\n");
		return (1);
	}
	return (0);
}

int check_files_names(t_map *map)
{
	int len;

	len = ft_strlen(map->east);
	if (map->east[len - 1] != 'm' && map->east[len - 2] != 'p' &&
		map->east[len - 3] != 'x' && map->east[len - 4] != '.')
			return (1);
	len = ft_strlen(map->west);
	if (map->west[len - 1] != 'm' && map->west[len - 2] != 'p' &&
		map->west[len - 3] != 'x' && map->west[len - 4] != '.')
			return (1);
	len = ft_strlen(map->south);
	if (map->south[len - 1] != 'm' && map->south[len - 2] != 'p' &&
		map->south[len - 3] != 'x' && map->south[len - 4] != '.')
			return (1);
	len = ft_strlen(map->north);
	if (map->north[len - 1] != 'm' && map->north[len - 2] != 'p' &&
		map->north[len - 3] != 'x' && map->north[len - 4] != '.')
			return (1);
	return (0);
}

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
	if (map->e_fd == -1 || map->w_fd == -1 || map->n_fd == -1 || map->s_fd == -1)
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

int fill_map_struct(char *map_file, t_map *map)
{
	map->fd = open(map_file, O_RDONLY);
	if (map->fd == -1)
	{
		printf("Can't open the map file!\n");
		return (1);
	}
	if (check_map_elements(map))
		return (1);
	if (check_files(map))
		return (1);
	map->copy_map = copy_map(map);
	if (map->copy_map == NULL)
		return (1);
	if (map_control(map))
		return (1);
	if (find_player_position(map))
		return (1);
	flood_fill(map, map->player->pos_x, map->player->pos_y, '0', 'F');
	if (flood_check(map, map->player->pos_x, map->player->pos_y))
	{
		printf("Map is not closed!!!\n");
		return (1);
	}
	find_start_position(map);
	double_map_flood(map, map->start_x, map->start_y);
	if (double_map_check(map))
		return (1);
	return (0);
}
