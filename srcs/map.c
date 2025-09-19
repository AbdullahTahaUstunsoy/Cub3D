#include "../includes/cube3D.h"

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
	char	*line;

	line = get_new_line(map->fd);
	while (line)
	{
		if (check_tab(line))
			map->flag = 1;
		
	}
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
}
