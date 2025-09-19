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
	if (fill_map_struct(av[1], map));
		return (1);
}
