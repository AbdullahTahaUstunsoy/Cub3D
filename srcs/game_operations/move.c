/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:49:15 by austunso          #+#    #+#             */
/*   Updated: 2025/10/26 15:49:18 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void  check_and_move(t_game *game, t_player *player ,double dir_x, double dir_y)
{
    char    **map;
    double  speed;
    double  new_x;
    double  new_y;

    map = game->map->map;
    speed = player->player_speed.move_speed;
    
    new_x = player->player_pos.pos_x + dir_x * speed;
    if (map[(int)player->player_pos.pos_y][(int)(player->player_pos.pos_x + dir_x * (speed + PADDING))] != '1')
        player->player_pos.pos_x = new_x;

    new_y = player->player_pos.pos_y + dir_y * speed;
    if (map[(int)(player->player_pos.pos_y + dir_y * (speed + PADDING))][(int)player->player_pos.pos_x] != '1')
        player->player_pos.pos_y = new_y;
}

static void    handle_translation(t_game *game, t_player *player)
{
    if (player->player_input.move_forward)
        check_and_move(game, player, player->player_pos.dir_x, player->player_pos.dir_y);
    if (player->player_input.move_backward)
        check_and_move(game, player, -player->player_pos.dir_x, -player->player_pos.dir_y);
    if (player->player_input.move_left)
        check_and_move(game, player, -player->player_pos.plane_x, -player->player_pos.plane_y);
    if (player->player_input.move_right)
        check_and_move(game, player, player->player_pos.plane_x, player->player_pos.plane_y);
}

static void rotate_player(t_player *player, double rot_speed)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = player->player_pos.dir_x;
	player->player_pos.dir_x = player->player_pos.dir_x * cos(rot_speed) - player->player_pos.dir_y * sin(rot_speed);
	player->player_pos.dir_y = old_dir_x * sin(rot_speed) + player->player_pos.dir_y * cos(rot_speed);

	old_plane_x = player->player_pos.plane_x;
	player->player_pos.plane_x = player->player_pos.plane_x * cos(rot_speed) - player->player_pos.plane_y * sin(rot_speed);
	player->player_pos.plane_y = old_plane_x * sin(rot_speed) + player->player_pos.plane_y * cos(rot_speed);
}

static void handle_rotation(t_player *player)
{
	if (player->player_input.rotate_left)
        rotate_player(player, -player->player_speed.rotation_speed);
    if (player->player_input.rotate_right)
        rotate_player(player, player->player_speed.rotation_speed);
}


void move(t_game *game)
{
	handle_translation(game, game->player);
	handle_rotation(game->player);
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