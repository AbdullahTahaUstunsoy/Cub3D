/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_components.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:48:57 by austunso          #+#    #+#             */
/*   Updated: 2025/10/26 15:48:59 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void set_direction(t_player *player)
{
    if (player->player_pos.player_dir == 'N')
    {
        player->player_pos.dir_x = 0;
        player->player_pos.dir_y = -1;
    }
    else if (player->player_pos.player_dir == 'S')
    {
        player->player_pos.dir_x = 0;
        player->player_pos.dir_y = 1;
    }
    else if (player->player_pos.player_dir == 'E')
    {
        player->player_pos.dir_x = 1;
        player->player_pos.dir_y = 0;
    }
    else
    {
        player->player_pos.dir_x = -1;
        player->player_pos.dir_y = 0;
    }
}

void set_player (t_player *player)
{
    player->player_pos.pos_x = player->player_pos.pos_x + 0.5; 
    player->player_pos.pos_y = player->player_pos.pos_y + 0.5;
}

void set_camera_plane (t_player *player)
{
    if (player->player_pos.player_dir == 'N')
    {
        player->player_pos.plane_x = 0.66;
        player->player_pos.plane_y = 0;
    }
    else if (player->player_pos.player_dir == 'S')
    {
        player->player_pos.plane_x = -0.66;
        player->player_pos.plane_y = 0;
    }
    else if (player->player_pos.player_dir == 'W')
    {
        player->player_pos.plane_x = 0;
        player->player_pos.plane_y = -0.66;
    }
    else // direction E
    {
        player->player_pos.plane_x = 0;
        player->player_pos.plane_y = 0.66;
    }
}

void set_player_speed (t_player *player)
{
	player->player_speed.move_speed = 0.10;
	player->player_speed.rotation_speed = 0.10;
}
