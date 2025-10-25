#include "../includes/cube3D.h"

void  check_and_move(t_game *game, double dir_x, double dir_y)
{
    char    **map;
    double  speed;
    double  padding;
    double  new_x;
    double  new_y;

    map = game->map->map;
    speed = game->player->move_speed;
    padding = 0.20; // Tampon bölge
    
    // X ekseninde hareket ve çarpışma kontrolü
    new_x = game->player->pos_x + dir_x * speed;
    if (map[(int)game->player->pos_y][(int)(game->player->pos_x + dir_x * (speed + padding))] != '1')
        game->player->pos_x = new_x;

    // Y ekseninde hareket ve çarpışma kontrolü
    new_y = game->player->pos_y + dir_y * speed;
    if (map[(int)(game->player->pos_y + dir_y * (speed + padding))][(int)game->player->pos_x] != '1')
        game->player->pos_y = new_y;
}

void    handle_translation(t_game *game)
{
    // İleri (W) - Yön vektörünü kullan
    if (game->player->move_forward)
        check_and_move(game, game->player->dir_x, game->player->dir_y);
    // Geri (S) - Yön vektörünün tersini kullan
    if (game->player->move_backward)
        check_and_move(game, -game->player->dir_x, -game->player->dir_y);
    // Sol (A) - Kamera düzleminin (plane) tersini kullan
    if (game->player->move_left)
        check_and_move(game, -game->player->plane_x, -game->player->plane_y);
    // Sağ (D) - Kamera düzlemini (plane) kullan
    if (game->player->move_right)
        check_and_move(game, game->player->plane_x, game->player->plane_y);
}

void rotate_player(t_player *player, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed) - player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed) + player->dir_y * cos(rot_speed);

	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed) - player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed) + player->plane_y * cos(rot_speed);
}

void handle_rotation(t_game *game)
{
	if (game->player->rotate_left)
        rotate_player(game->player, -game->player->rotation_speed);
    if (game->player->rotate_right)
        rotate_player(game->player, game->player->rotation_speed);
}


void move(t_game *game)
{
	handle_translation(game);
	handle_rotation(game);
}




/*void move(t_game *game)
{
    double  new_x;
    double  new_y;
    char    **map;

    map = game->map->map;

    if (game->player->move_forward)
    {
        new_x = game->player->pos_x + game->player->dir_x * game->player->move_speed;
        double check_x = game->player->pos_x + game->player->dir_x * (game->player->move_speed + PADDING);
        if (map[(int)game->player->pos_y][(int)check_x] != '1')
            game->player->pos_x = new_x;
        
        new_y = game->player->pos_y + game->player->dir_y * game->player->move_speed;
        double check_y = game->player->pos_y + game->player->dir_y * (game->player->move_speed + PADDING);
        if (map[(int)check_y][(int)game->player->pos_x] != '1')
            game->player->pos_y = new_y;
    }
    if (game->player->move_backward)
    {
        new_x = game->player->pos_x - game->player->dir_x * game->player->move_speed;
        double check_x = game->player->pos_x - game->player->dir_x * (game->player->move_speed + PADDING);
        if (map[(int)game->player->pos_y][(int)check_x] != '1')
            game->player->pos_x = new_x;
        
        new_y = game->player->pos_y - game->player->dir_y * game->player->move_speed;
        double check_y = game->player->pos_y - game->player->dir_y * (game->player->move_speed + PADDING);
        if (map[(int)check_y][(int)game->player->pos_x] != '1')
            game->player->pos_y = new_y;
    }
    if (game->player->move_left)
    {
        new_x = game->player->pos_x - game->player->plane_x * game->player->move_speed;
        double check_x = game->player->pos_x - game->player->plane_x * (game->player->move_speed + PADDING);
        if (map[(int)game->player->pos_y][(int)check_x] != '1')
            game->player->pos_x = new_x;

        new_y = game->player->pos_y - game->player->plane_y * game->player->move_speed;
        double check_y = game->player->pos_y - game->player->plane_y * (game->player->move_speed + PADDING);
        if (map[(int)check_y][(int)game->player->pos_x] != '1')
            game->player->pos_y = new_y;
    }
    if (game->player->move_right)
    {
        new_x = game->player->pos_x + game->player->plane_x * game->player->move_speed;
        double check_x = game->player->pos_x + game->player->plane_x * (game->player->move_speed + PADDING);
        if (map[(int)game->player->pos_y][(int)check_x] != '1')
            game->player->pos_x = new_x;
            
        new_y = game->player->pos_y + game->player->plane_y * game->player->move_speed;
        double check_y = game->player->pos_y + game->player->plane_y * (game->player->move_speed + PADDING);
        if (map[(int)check_y][(int)game->player->pos_x] != '1')
            game->player->pos_y = new_y;
    }
    
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
}*/