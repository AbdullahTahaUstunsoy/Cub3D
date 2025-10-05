#include "../includes/cube3D.h"

int check_map_name(char *str)
{
	int	i;
	int	flag;

	flag = 0;
	i = ft_strlen(str);
	if (str[i - 1] != 'b')
		flag = 1;
	else if (str[i - 2] != 'u')
		flag = 1;
	else if (str[i - 3] != 'c')
		flag = 1;
	else if (str[i - 4] != '.')
		flag = 1;
	if (flag == 1)
		printf("Wrong file name!\n");
	return (flag);
}

int main(int ac, char **av)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (ac != 2)
	{
		printf("Wrong argument count!\n");
		return (1);
	}
	if (check_map_name(av[1]))
		return (1);
	if (fill_map_struct(av[1], map))
		return (1);
	printf("Map_fd:   %d\n", map->fd);
	printf("North:    %s\n", map->north);
	printf("North_fd: %d\n", map->n_fd);
	printf("East:     %s\n", map->east);
	printf("East_fd:  %d\n", map->e_fd);
	printf("South:    %s\n", map->south);
	printf("South_fd: %d\n", map->s_fd);
	printf("West:     %s\n", map->west);
	printf("West_fd:  %d\n", map->w_fd);
	printf("Ceiling:  %d\n", map->ceiling);
	printf("Floor:    %d\n", map->floor);
	int i = 0;
	while (i < 16)
	{
		printf("%s\n",map->map[i]);
		i++;
	}
	printf("\n\n\n\n\n");
	i = 0;
	while (i < 16)
	{
		printf("%s\n",map->copy_map[i]);
		i++;
	}
	return (0);
}
