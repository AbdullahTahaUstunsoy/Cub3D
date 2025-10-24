#include "../includes/cube3D.h"

//color, r g b kullandım mı ? r << 16, g << 8 , b yapısını şuan göremedim gerekli mi ?
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
	else if (str[i - 5] == '/') // OLMALI MI OLMAMALAI MI TAHAYA SORRRRRRRRR
		flag = 1;
	if (flag == 1)
		printf("Wrong file name!\n");
	return (flag);
}


void set_player (t_player *player)
{
    player->pos_x = player->pos_x + 0.5; 
    player->pos_y = player->pos_y + 0.5;
}

void set_player_speed (t_player *player)
{
	player->move_speed = 0.10;
	player->rotation_speed = 0.10;
}

void set_camera_plane (t_player *player)
{
	if (player->player_dir == 'N')
	{
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->player_dir == 'S')
	{
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (player->player_dir == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else // direction E
	{
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
}
void set_direction(t_player *player)
{
    if (player->player_dir == 'N')
    {
        player->dir_x = 0;
        player->dir_y = -1;
    }
    else if (player->player_dir == 'S')
    {
        player->dir_x = 0;
        player->dir_y = 1;
    }
    else if (player->player_dir == 'E')
    {
        player->dir_x = 1;
        player->dir_y = 0;
    }
    else
    {
        player->dir_x = -1;
        player->dir_y = 0;
    }
}

void step_and_sideDist(t_ray *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

void perform_dda(t_ray *ray, t_player *player, t_map *map)
{
	while (player->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // dikey duvara çarptık
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // yatay duvara çarptık
		}
		// Çarpışma kontrolü
		if (map->map[ray->map_y][ray->map_x] == '1') // duvar hücresi
			player->hit = 1; // çarpışma gerçekleşti
	}
}

void calculate_wall_distance(t_ray *ray)
{	
	if (ray->side == 0) // dikey duvara çarptık
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else // yatay duvara çarptık
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

void height_of_line_to_draw(t_ray *ray)
{
	ray->wall_height = (int)(SCREEN_HEIGHT / ray->perp_wall_dist);
	ray->wall_start = -ray->wall_height / 2 + SCREEN_HEIGHT / 2;
	if(ray->wall_start < 0)
		ray->wall_start = 0;
	ray->wall_end = ray->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->wall_end >= SCREEN_HEIGHT)
		ray->wall_end = SCREEN_HEIGHT - 1;
}


void init_rays (t_ray *ray, t_player *player, int column)
{

	ray->camera_x = 2 * column / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x; // map_x ve map_y oyuncunun bulunduğu hücreyi gösterir
	ray->map_y = (int)player->pos_y;
	player->hit = 0;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30; // sonsuz büyük bir değer
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void determine_texture_number(t_ray *ray)
{
	if (ray->side == 0 && ray->ray_dir_x >= 0)
		ray->tex_num = 0;
	else if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_num = 1;
	else if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex_num = 2;
	else
		ray->tex_num = 3;
}

static int	get_color(t_texture *img, int x, int y)
{
	return (*(size_t *)(img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)))); //Texture'dan alınan rengi belirler.
}

static void	put_pixel(t_texture *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) //Eğer pixel ekrandan dışarıda kalıyorsa fonksiyonu sonlandırırız.
		return ;
	if (!img->addr)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8)); //Koyduğumuz pixelin tam ve kesin adresini belirler(Adresin başlangıcı + (y * satır uzunluğu + x * pixelin bit uzunluğu / 8)) -> (satır uzunluğu = ekran genişliği * 4)
	*(unsigned int *)dst = color; //Bu adresin içine color değerini atarız.
}

void load_textures(t_game *game)
{
	//NULL kontrollerini ekle
	// printf("NORTH TEXTURE = %s\n", game->map->north);
	// printf("SOUTH TEXTURE = %s\n", game->map->south);
	// printf("EAST TEXTURE = %s\n", game->map->east);
	// printf("WEST TEXTURE = %s\n", game->map->west);
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx, game->map->north, //textures[0] -> North texture , textures[1] -> South texture , textures[2] -> East texture , textures[3] -> West texture
			&game->textures[0].width, &game->textures[0].height);
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img,
			&game->textures[0].bits_per_pixel, &game->textures[0].line_length,
			&game->textures[0].endian);
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx, game->map->south,
			&game->textures[1].width, &game->textures[1].height);
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].img,
			&game->textures[1].bits_per_pixel, &game->textures[1].line_length,
			&game->textures[1].endian);
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx, game->map->east,
			&game->textures[2].width, &game->textures[2].height);
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].img,
			&game->textures[2].bits_per_pixel, &game->textures[2].line_length,
			&game->textures[2].endian);
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx, game->map->west,
			&game->textures[3].width, &game->textures[3].height);
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].img,
			&game->textures[3].bits_per_pixel, &game->textures[3].line_length,
			&game->textures[3].endian);
}

void draw_pixels(t_ray *ray, int column, t_game *game)
{
	// ray->wall_x'i hesapla (duvarın tam olarak neresine çarptık?)
    if (ray->side == 0) // Dikey duvar
		ray->wall_x = game->player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
    else // Yatay duvar
		ray->wall_x = game->player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	determine_texture_number(ray);
	ray->wall_x -= floor(ray->wall_x); //Texture'ın hangi konumda başlayacağını belirler. (Örneğin 3.5 bir duvara çarptıysak texture 0.5 konumunda başlayacak. Duvarı 1'e 1'lik bir texutre ile kaplarsak 0.5'ten başlayarak 1'e kadar olan kısmı duvara çizeriz. Çünkü diğer türlü texture yanlış çizilir.)
	ray->tex_x = (int)(ray->wall_x * (double)64); //Texture 64x64 olduğu için başlangıç pixelini 64 ile çarparız. Bu sayede textureda doğru konumundan çizmeye başlarız.
	if ((ray->ray_dir_x < 0 && ray->side == 0) || (ray->ray_dir_y > 0 && ray->side == 1)) //Eğer duvar x ekseninde bir duvar ise ve rayin x yönündeki hareketi pozitifse dokuyu tersten çizmemiz gerekir.
		ray->tex_x = 64 - ray->tex_x - 1; //Bu yüzden texture'ı tersten çizmek için texture'ın başlangıç pixelini 64'ten çıkarırız.
	ray->draw_step = 1.0 * 64 / ray->wall_height; //Duvarın yüksekliğine göre texture'ın çizilme adımını belirler. (Duvar büyükse pixelleri daha büyük çizmemiz gerekir, küçükse daha küçük çizmemiz gerekir.)
	ray->tex_pos = (ray->wall_start - SCREEN_HEIGHT / 2 + ray->wall_height / 2) * ray->draw_step;
	size_t y;
	t_texture *tmp;

	tmp = &game->textures[ray->tex_num]; //Hangi texture'ı kullanacağımızı belirler.
	y = -1;
	while (++y < SCREEN_HEIGHT)
	{
		if (y < ray->wall_start)
			put_pixel(&game->img, column, y, game->map->ceiling);
		else if (y < (size_t)ray->wall_end)
		{
			ray->tex_y = (int)ray->tex_pos % 64; //Texture'ın 0-63 sınırları arasında kalmasını sağlar. (Texture 64x64 olduğu için 64'e modunu alırız)
			ray->tex_pos += ray->draw_step; //Çizgi uzunluğuna göre hesapladığımız step kadar texture'ın pozisyonunu güncelleriz.
			ray->color = get_color(tmp, ray->tex_x, ray->tex_y); //Texture'dan alınan rengi belirler.
			put_pixel(&game->img, column, y, ray->color); //Texture'dan alınan rengi çizer.
		}
		else
			put_pixel(&game->img, column, y, game->map->floor);
	}
}

void raycast(t_ray *ray, t_player *player, t_game *game)
{
	int column;

	column = 0;
	while (column < SCREEN_WIDTH)
	{
		init_rays(ray, player, column);
		//----------------------Calculate step and initial sideDist---------------
		step_and_sideDist(ray, player);
		//----------------------Perform DDA---------------------------------------
		perform_dda(ray, player, game->map);
		//----------------------Calculate distance to the wall--------------------
		calculate_wall_distance(ray);
		//----------------------Calculate height of line to draw on screen--------	
		height_of_line_to_draw(ray);
		//---------------------- choose wall color--------------------------------
		draw_pixels(ray, column, game); //textured kısmı başladı.
		//birkaç fonksiyon daha eklememiz gerekebilir.
		column++;
	}
}

void render(t_game *game)
{
    raycast(game->ray, game->player, game);
    mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
    // isteğe bağlı: mlx_destroy_image(game->mlx, game->img.img);
}

void init_keys(t_game *game)
{
	game->player->move_forward = 0;
	game->player->move_backward = 0;
	game->player->move_left = 0;
	game->player->move_right = 0;
	game->player->rotate_left = 0;
	game->player->rotate_right = 0;
}


void move(t_game *game)
{
    double  new_x;
    double  new_y;
    char    **map;
    // Oyuncunun "yarıçapı" gibi davranacak bir tampon bölge.
    // Duvara bu kadar mesafe kala durmasını sağlar.
    // Genellikle hareket hızından biraz büyük olması iyi çalışır.
    double  padding = 0.20; 

    map = game->map->map;

    if (game->player->move_forward)
    {
        // 1. Gideceği YENİ X KONUMUNU hesapla
        new_x = game->player->pos_x + game->player->dir_x * game->player->move_speed;
        // 2. O konumun "tamponlu" halini (check_x) hesapla
        double check_x = game->player->pos_x + game->player->dir_x * (game->player->move_speed + padding);
        // 3. "check_x" bir duvara çarpmıyorsa, asıl "new_x" konumuna git
        if (map[(int)game->player->pos_y][(int)check_x] != '1')
            game->player->pos_x = new_x;
        
        // 4. Y için aynı mantık
        new_y = game->player->pos_y + game->player->dir_y * game->player->move_speed;
        double check_y = game->player->pos_y + game->player->dir_y * (game->player->move_speed + padding);
        if (map[(int)check_y][(int)game->player->pos_x] != '1')
            game->player->pos_y = new_y;
    }
    if (game->player->move_backward)
    {
        new_x = game->player->pos_x - game->player->dir_x * game->player->move_speed;
        double check_x = game->player->pos_x - game->player->dir_x * (game->player->move_speed + padding);
        if (map[(int)game->player->pos_y][(int)check_x] != '1')
            game->player->pos_x = new_x;
        
        new_y = game->player->pos_y - game->player->dir_y * game->player->move_speed;
        double check_y = game->player->pos_y - game->player->dir_y * (game->player->move_speed + padding);
        if (map[(int)check_y][(int)game->player->pos_x] != '1')
            game->player->pos_y = new_y;
    }
    if (game->player->move_left) // Sağa/Sola (Strafe) plane vektörünü kullanır
    {
        new_x = game->player->pos_x - game->player->plane_x * game->player->move_speed;
        double check_x = game->player->pos_x - game->player->plane_x * (game->player->move_speed + padding);
        if (map[(int)game->player->pos_y][(int)check_x] != '1')
            game->player->pos_x = new_x;

        new_y = game->player->pos_y - game->player->plane_y * game->player->move_speed;
        double check_y = game->player->pos_y - game->player->plane_y * (game->player->move_speed + padding);
        if (map[(int)check_y][(int)game->player->pos_x] != '1')
            game->player->pos_y = new_y;
    }
    if (game->player->move_right)
    {
        new_x = game->player->pos_x + game->player->plane_x * game->player->move_speed;
        double check_x = game->player->pos_x + game->player->plane_x * (game->player->move_speed + padding);
        if (map[(int)game->player->pos_y][(int)check_x] != '1')
            game->player->pos_x = new_x;
            
        new_y = game->player->pos_y + game->player->plane_y * game->player->move_speed;
        double check_y = game->player->pos_y + game->player->plane_y * (game->player->move_speed + padding);
        if (map[(int)check_y][(int)game->player->pos_x] != '1')
            game->player->pos_y = new_y;
    }
    
    // Dönme hareketleri (Bunlar doğru, değiştirmeye gerek yok)
    if (game->player->rotate_left)
    {
        double old_dir_x = game->player->dir_x;
        game->player->dir_x = game->player->dir_x * cos(-game->player->rotation_speed) - game->player->dir_y * sin(-game->player->rotation_speed);
        game->player->dir_y = old_dir_x * sin(-game->player->rotation_speed) + game->player->dir_y * cos(-game->player->rotation_speed);
        double old_plane_x = game->player->plane_x;
        game->player->plane_x = game->player->plane_x * cos(-game->player->rotation_speed) - game->player->plane_y * sin(-game->player->rotation_speed);
        game->player->plane_y = old_plane_x * sin(-game->player->rotation_speed) + game->player->plane_y * cos(-game->player->rotation_speed);
    }
    if (game->player->rotate_right)
    {
        double old_dir_x = game->player->dir_x;
        game->player->dir_x = game->player->dir_x * cos(game->player->rotation_speed) - game->player->dir_y * sin(game->player->rotation_speed);
        game->player->dir_y = old_dir_x * sin(game->player->rotation_speed) + game->player->dir_y * cos(game->player->rotation_speed);
        double old_plane_x = game->player->plane_x;
        game->player->plane_x = game->player->plane_x * cos(game->player->rotation_speed) - game->player->plane_y * sin(game->player->rotation_speed);
        game->player->plane_y = old_plane_x * sin(game->player->rotation_speed) + game->player->plane_y * cos(game->player->rotation_speed);
    }
}

int game_loop (t_game *game)
{
	move(game);
	render(game); //hareket edemiyorusa return 0 olup ne olacak ?
	return 0;
}

void set_mlx(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	mlx_hook(game->win, 2, 1L<<0, press_the_key, game);
	mlx_hook(game->win, 3, 1L<<1, release_the_key, game);
	mlx_hook(game->win, 17, 0, close_the_window, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}

void	map_init(t_game *game)
{
	game->map->fd = -2;
	game->map->start_x = -1;
	game->map->start_y = -1;
	game->map->e_fd = -2;
	game->map->s_fd = -2;
	game->map->n_fd = -2;
	game->map->w_fd = -2;
	game->map->map_height = 0;
	game->map->ceiling = -1;
	game->map->floor = -1;
	game->map->north = NULL;
	game->map->south = NULL;
	game->map->east = NULL;
	game->map->west = NULL;
	game->map->player = game->player; // bu saçma mı oldu
}


int init_main_img(t_game *game)
{
	game->img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img.img)
	{
		printf("Error: Image could not be created!\n");
		//destroy free durumunu ayarla
		return (1);
	}
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel, &game->img.line_length,
			&game->img.endian);
	if (!game->img.addr)
	{
		printf("Error : Image address could not be taken!\n");
		//destroy free durumunu ayarla
		return (1);
	}
	return (0);
}


void *free_game(t_game *game)
{
	if (game->player)
		free(game->player);
	if (game->map)
		free(game->map);
	if (game->ray)
		free(game->ray);
	free(game);
	return (NULL);
}

t_game *init_structs(void)
{
	// bu structları kendi içinde başlatmalı mıyım ?
	t_game *game;
	
	game = ft_calloc(1, sizeof(t_game));
	if(!game)
		return (NULL);
	game->player = ft_calloc(1,sizeof(t_player));
	if(game->player == NULL)
		return(free_game(game));
	game->map = ft_calloc(1,sizeof(t_map));
	if(game->map == NULL)
		return(free_game(game));
	game->ray = ft_calloc(1,sizeof(t_ray));
	if(game->ray == NULL)
		return(free_game(game));
	return (game);
}
int set_game_components(t_game *game)
{
	set_mlx(game);
	if(init_main_img(game))
		return (1);
	init_keys(game);
	set_direction(game->player);
	set_player(game->player);
	set_camera_plane(game->player);
	set_player_speed(game->player);
	return (0);
}
int check_initial_conditions (t_game *game, int argc)
{
	if (game == NULL)
	{
		printf("An error occured while initializing structs!\n");
		return (1);
	}
	if (argc != 2)
	{
		printf("Wrong argument count!\n");
		return (1);
	}
	return (0);
}


int main(int ac, char **av)
{
	t_game *game;

	game = init_structs();
	if (check_initial_conditions(game,ac))
		return (1);
	if (map_operations(game,av))
		return (1);
	if (set_game_components(game))
		return (1);
	load_textures(game);
	render(game);
	mlx_loop(game->mlx);
	return (0);
}
