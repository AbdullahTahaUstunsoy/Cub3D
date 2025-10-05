#include "../includes/cube3D.h"

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

int	map_control(t_map *map)
{
	int		i;
	size_t	length;
	int 	j;
	int 	count;
	char	*new_line;

	i = -1;
	j = -1;
	length = find_longest_line(map);
	while (map->copy_map[++i] != NULL)
	{
		if (length > ft_strlen(map->copy_map[i]))
		{
			count = length - ft_strlen(map->copy_map[i]);
			new_line = malloc(sizeof(char) * (length + 1));
			ft_memcpy(new_line, map->copy_map[i], ft_strlen(map->copy_map[i]));
			j = ft_strlen(map->copy_map[i]);
			while (count-- > 0)
			{
				new_line[++j] = 'a';
			}
			new_line[++j] = '\0';
			free(map->copy_map[i]);
			map->copy_map[i] = ft_strdup(new_line);
			free(new_line);
		}
	}
	return (0);
}

int	map_fill(t_map *map, char *line, int map_size)
{
	int		i;
	char	**new_map;
	char	**new_copy;

	i = 0;
	map->map_height++;
	new_map = malloc((map_size + 1) * sizeof(char *));
	new_copy = malloc((map_size + 1) * sizeof(char *));
	if (!new_copy)
		return (1);
	if (!new_map)
		return (1);
	while(i < map_size)
	{
		new_map[i] = map->map[i];
		new_copy[i] = map->copy_map[i];
		i++;
	}
	new_map[map_size] = ft_strdup(line);
	free(map->map);
	map->map = new_map;
	map->copy_map = new_copy;
	return (0);
}
