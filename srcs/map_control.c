#include "../includes/cube3D.h"

int	flood_check(t_map *map, int x, int y)
{
	if (y < 0 || x < 0 || !map->copy_map[y] || map->copy_map[y][x] == '\0')
		return (1);
	if (map->copy_map[y][x] == '1' || map->copy_map[y][x] == 'F')
		return (0);
	if (map->copy_map[y][x] == ' ' || map->copy_map[y][x] == '*')
		return (1);

	map->copy_map[y][x] = 'F';

	return (
		flood_check(map, x + 1, y) ||
		flood_check(map, x - 1, y) ||
		flood_check(map, x, y + 1) ||
		flood_check(map, x, y - 1)
	);
}

void	flood_fill(t_map *map, int x, int y, char target, char fill)
{
	if (map->copy_map[y][x] != target)
		return;
	map->copy_map[y][x] = fill;

	flood_fill(map, x + 1, y, target, fill);
	flood_fill(map, x - 1, y, target, fill);
	flood_fill(map, x, y + 1, target, fill);
	flood_fill(map, x, y - 1, target, fill);
}

int fill_player_struct(int x, int y, int flag, t_map *map)
{
	if (!flag)
	{
		map->player->pos_x = (double)x;
		map->player->pos_y = (double)y;
		map->map[y][x] = '0';
		map->copy_map[y][x] = '0';
		map->player->player_dir = map->copy_map[y][x];
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
	while(map->copy_map[++y] != NULL)
	{
		x = 0;
		while(map->copy_map[y][++x] != '\0')
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
	return (0);
}

int	character_check(t_map *map)
{
	int	i;
	int	j;
	int	flag;
	char	c;

	i = 0;
	flag = 0;
	while(map->map[i] != NULL)
	{
		j = 0;
		while(map->map[i][j] != '\0')
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
				&& map->map[i][j] != ' ')
					if (map->map[i][j] != 'N' && map->map[i][j] != 'S'
				&& map->map[i][j] != 'E' && map->map[i][j] != 'W')
				{
					flag = 1;
					c = map->map[i][j];	
				}
					
			j++;
		}
		i++;
	}
	if (flag)
	{
		printf("Invalid character in map %c!!\n", c);
		return (1);
	}
	return (0);
}

int find_longest_line(t_map *map)
{
	int	i;
	int	length;
	int	tmp;

	i = 0;
	length = 0;
	while(map->map[i] != NULL)
	{
		tmp = ft_strlen(map->map[i]);
		if (tmp > length)
			length = tmp;
		i++;
	}
	return (length);
}

int map_control(t_map *map)
{
	int		i;
	size_t	length;
	size_t	tmp;
	char	*new_line;

	i = -1;
	length = find_longest_line(map);
	while (map->copy_map[++i] != NULL)
	{
		tmp = ft_strlen(map->copy_map[i]);
		if (tmp < length)
		{
			new_line = malloc(length + 1);
			if (!new_line)
				return (1);
			ft_memcpy(new_line, map->copy_map[i], tmp);
			while (tmp < length)
				new_line[tmp++] = '*';
			new_line[length] = '\0';
			free(map->copy_map[i]);
			map->copy_map[i] = new_line;
		}
	}
	
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
	map->map_height++;
	new_map = malloc((map_size + 1) * sizeof(char *));

	if (!new_map)
		return (1);
	while(i < map_size)
	{
		new_map[i] = map->map[i];
		i++;
	}
	new_map[map_size] = ft_strdup(line);
	free(map->map);
	map->map = new_map;
	return (0);
}
