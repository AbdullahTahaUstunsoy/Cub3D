#ifndef CUB3D_H
#define CUB3D_H


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
#define EAST 0
#define WEST 1
#define SOUTH 2
#define NORTH 3


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "../minilibx-linux/mlx.h"
#include "../get_next_line/get_next_line.h"

typedef struct s_player_pos
{
	char player_dir;
	double pos_x;
	double pos_y;
	double plane_x;
	double plane_y;
	double dir_x;
	double dir_y;
}				t_player_pos;

typedef struct s_player_input
{
	int		move_forward;
	int		move_backward;
	int		move_left;
	int		move_right;
	int		rotate_left;
	int		rotate_right;
}		t_player_input;

typedef struct s_player_speed
{
	double	move_speed;
	double	rotation_speed;
}		t_player_speed;

typedef struct s_player
{
	t_player_pos		player_pos;
	t_player_input		player_input;
	t_player_speed		player_speed;
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
	int			map_size;
	char		**map;
	char		**copy_map;
	t_player	*player;

}				t_map;

typedef struct s_ray_calc
{
	double  camera_x;
    double  ray_dir_x;
    double  ray_dir_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;
}	t_ray_calc;


typedef struct s_draw_params
{
	double  wall_x;
    double  draw_step;
    double  tex_pos;
    int     color;
    int     tex_y;
    int     tex_x;
    int     tex_num;
    double  wall_height;
    double  wall_start;
    double  wall_end;
}	t_draw_params;

typedef struct  s_ray
{
	t_ray_calc      ray_calc;
    t_draw_params   ray_draw;
}				t_ray;

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

typedef struct s_mlx_content
{
	void	*mlx;
	void	*win;
}				t_mlx_content;

typedef struct s_game
{
	t_ray 		*ray;
	t_mlx_content mlx_content;
	t_texture	textures[4];
	t_texture	img;
	t_map		*map;
	t_player	*player;
}				t_game;

int press_the_key(int keycode, void *param);
int release_the_key(int keycode, void *param);
int close_the_window(void *param);



int	map_fill(t_map *map, char *line, int map_size);
int	map_control(t_map *map);
char	**copy_map(t_map *map);
int	find_player_position(t_map *map);
void	flood_fill(t_map *map, int x, int y, char target);
int		flood_check(t_map *map, int x, int y);

void	set_player(t_player *player);
void	set_camera_plane(t_player *player);
void	set_player_speed(t_player *player);
int map_operations(t_game *game, char **av);
void	map_init(t_game *game);
int check_map_name(char *str);
int fill_map_struct(char *map_file, t_map *map);

int set_game_components(t_game *game);
int init_main_img(t_game *game);
int set_mlx(t_game *game);

void init_keys(t_game *game);

void set_direction(t_player *player);
void set_player (t_player *player);
void set_camera_plane (t_player *player);
void set_player_speed (t_player *player);

t_game *init_structs(void);


void raycast(t_ray *ray, t_player *player, t_game *game);
void render(t_game *game);
int game_loop (t_game *game);

void draw_pixels(t_ray *ray, int column, t_game *game, t_player *player);

void init_rays (t_ray *ray, t_player *player, int column);
void step_and_sideDist(t_ray *ray, t_player *player);
void perform_dda(t_ray *ray, t_map *map);
void calculate_wall_distance(t_ray *ray);
void height_of_line_to_draw(t_ray *ray);
int load_textures(t_game *game);
void move(t_game *game);

void free_mlx(t_game *game);
void *free_game(t_game *game);
void	free_all(t_game *game);
void	free_array(char **str);
void    free_map_contents(t_map *map);
int		map_operations(t_game *game, char **av);
void	map_init(t_game *game);
int		check_map_name(char *str);
int		fill_map_struct(char *map_file, t_map *map);
void	*free_game(t_game *game);
int		check_invalid_map_line(char *line);
int		ft_isvalid(char *str);
int		check_coloring(char *line);
int		check_identifiers(t_map *map, char *identifier);
int		check_tab(char *str);
int		check_files(t_map *map);
int		check_files_names(t_map *map);
int		check_map_elements(t_map *map);
char	*adjust_line(t_map *map, char *line, int count);
int		map_elements(t_map *map, char *trimmed_line, char *line, int count);
int		flood_check(t_map *map, int x, int y);
int		fill_player_struct(int x, int y, int flag, t_map *map);
int		find_player_position(t_map *map);
int		find_longest_line(t_map *map);

#endif