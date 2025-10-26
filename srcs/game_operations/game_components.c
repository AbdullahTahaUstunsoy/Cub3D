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

void set_player (t_player *player)
{
    player->pos_x = player->pos_x + 0.5; 
    player->pos_y = player->pos_y + 0.5;
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

void set_player_speed (t_player *player)
{
	player->move_speed = 0.10;
	player->rotation_speed = 0.10;
}
