#include "../includes/cube3D.h"

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
		return (-1);
	numbers = ft_split(line, ',');
	if (!numbers)
		return (-1);
	if (!numbers[0] || !numbers[1] || !numbers[2] || numbers[3] != NULL)
	{
		free_array(numbers);
		return (-1);
	}
	r = ft_isvalid(numbers[0]);
	g = ft_isvalid(numbers[1]);
	b = ft_isvalid(numbers[2]);
	free_array(numbers);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int	check_identifiers(t_map *map, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		map->north = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->south = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->west = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->east = ft_strdup(line + 3);
	else if (ft_strncmp(line, "NO ", 3) == 0)
		map->north = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		map->floor = check_coloring(ft_strtrim((line + 1), " "));
	else if (ft_strncmp(line, "C ", 2) == 0)
		map->ceiling = check_coloring(ft_strtrim((line + 1), " "));
	else
	{
		printf("Wrong map identifier\n");
		return (1);
	}
	if (map->floor == -1 || map->ceiling == -1)
	{
		printf("Wrong color input\n");
		return (1);
	}
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
	int		i;
	char	*trimmed_line;
	int		map_size;

	map_size = 0;
	count = 0;
	i = 0;
	map->map = malloc(sizeof(char *));
	while ((line = get_next_line(map->fd)))
	{
		if (check_tab(line))
			map->flag = 1;
		trimmed_line = ft_strtrim(line, "\n");
		
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
				return (1);
		}
/* 		else if (check_map_lines(trimmed_line))
			return(1); */
		else 
		{
			if (map_fill(map, trimmed_line, map_size))
				return (1);
			
			map_size++;
		}
		free(line);
		free(trimmed_line);
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
	map_control(map);
	return (0);
}
