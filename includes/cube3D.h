#ifndef CUBE3D_H
#define CUBE3D_H


#define SCREEN_HEIGHT 1080
#define SCREEN_WIDTH 1920
# define M_PI 3.14159265358979323846
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307
#define PADDING 0.20

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../get_next_line/get_next_line.h"

typedef struct s_player
{
	char player_dir; // oyuncunun yönünü tutacak -> N,S,E,W
	double pos_x; // oyuncunun x koordinatı //bunlar henüz bulunmadı sanırım 
	double pos_y; // oyuncunun y koordinatı //bunlar henüz bulunmadı sanırım 
	double plane_x; // kamera düzlemi x bileşeni
	double plane_y; // kamera düzlemi y bileşeni
	double dir_x; // yön vektörünün x bileşeni
	double dir_y; // yön vektörünün y bileşeni
	double move_speed;
	double rotation_speed;
	int		hit;
	int		move_forward;
	int		move_backward;
	int		move_left;
	int		move_right;
	int		rotate_left;
	int		rotate_right;
}           t_player;

typedef struct s_map
{
	int			fd;
	int			start_x;
	int			start_y;
	int			e_fd;
	int			n_fd;
	int			s_fd;
	int			w_fd;
	int			flag;
	char		*north;
	char		*east;
	char		*south;
	char		*west;
	int			ceiling;
	int			floor;
	int			map_height;
	char		**map;
	char		**copy_map;
	t_player	*player;

}				t_map;



typedef struct  s_ray
{
	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	double perp_wall_dist;
	double wall_x;
	double draw_step;
	double tex_pos;
	int color;
	int tex_y;
	int tex_x;
	int map_x;
	int map_y;
	int step_x;
	int step_y;
	int hit;
	int side;
	int tex_num;
	double wall_height;
	double wall_start;
	double wall_end;
}				t_ray;

typedef struct s_color //henüz kullnmadım
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_texture;

typedef struct s_game
{
	t_ray 		*ray;
	void		*mlx;
	void		*win;
	t_texture	textures[4];
	t_texture	img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_map		*map;
	t_player	*player;
}				t_game;

int press_the_key(int keycode, void *param);
int release_the_key(int keycode, void *param);
int close_the_window(void *param);



void	free_array(char **str);
int	map_fill(t_map *map, char *line, int map_size);
int	map_control(t_map *map);
char	**copy_map(t_map *map);
int	find_player_position(t_map *map);
void	flood_fill(t_map *map, int x, int y, char target, char fill);
int		flood_check(t_map *map, int x, int y);

void	assign_direction(t_player *player);
void	set_player(t_player *player);
void	set_camera_plane(t_player *player);
void	set_player_speed(t_player *player);
void	free_all(t_game *game);
int map_operations(t_game *game, char **av);
void	map_init(t_game *game);
int check_map_name(char *str);
int fill_map_struct(char *map_file, t_map *map);
void *free_game(t_game *game);

int set_game_components(t_game *game);
int init_main_img(t_game *game);
void set_mlx(t_game *game);

void init_keys(t_game *game);

void set_direction(t_player *player);
void set_player (t_player *player);
void set_camera_plane (t_player *player);
void set_player_speed (t_player *player);

t_game *init_structs(void);
int check_initial_conditions (t_game *game, int argc);


void raycast(t_ray *ray, t_player *player, t_game *game);
void render(t_game *game);
int game_loop (t_game *game);

void draw_pixels(t_ray *ray, int column, t_game *game);
int	get_color(t_texture *img, int x, int y);
void determine_texture_number(t_ray *ray);

void init_rays (t_ray *ray, t_player *player, int column);
void step_and_sideDist(t_ray *ray, t_player *player);
void perform_dda(t_ray *ray, t_player *player, t_map *map);
void calculate_wall_distance(t_ray *ray);
void height_of_line_to_draw(t_ray *ray);
void load_textures(t_game *game);
void move(t_game *game);

#endif