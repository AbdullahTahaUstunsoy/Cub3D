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
		if (str[i] != ' ' && (str[i] < '0' || str[i] > '9')) // yinr r den oluyor
		{
			printf("str C = %d\n", str[i]);
			printf("girdi mi\n");
			return (-1);
		}
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

	printf("coloring line == %s\n", line);
    if (!line)
	{
        return (-1);
	}
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
	printf("r = %d\n", r);
	printf("g = %d\n", g);
	printf("b = %d\n", b);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("girdi mi\n");
        return (-1);
	}
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
	char	*trimmed_line;

	count = 0;
	while ((line = get_next_line(map->fd)))
	{
		if (check_tab(line))
			map->flag = 1;
		trimmed_line = ft_strtrim(line, " ");
		if (trimmed_line[0] == '\0' || trimmed_line[0] == '\n'|| trimmed_line[0] == '\r') // r windows için eklendi
		{
			free(line);
			free(trimmed_line);
			continue;
		}
		count++;
		if (count < 6)
		{
			if (check_identifiers(map, trimmed_line))
				return (1);
		}
		else
		{
			printf("map_control\n");
			return (0);
			
		}
		free(line);
		free(trimmed_line);
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
	return (0);
}
