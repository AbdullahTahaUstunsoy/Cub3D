/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: austunso <austunso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 15:49:32 by austunso          #+#    #+#             */
/*   Updated: 2025/10/26 15:49:34 by austunso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int press_the_key(int keycode, void *param)
{
    t_game *game;
    t_player *player;

    game = (t_game *)param;
    player = game->player;
    if (keycode == KEY_ESC)
        close_the_window(param);
    if (keycode == KEY_W)
        player->player_input.move_forward = 1;
    if (keycode == KEY_S)
        player->player_input.move_backward = 1;
    if (keycode == KEY_A)
        player->player_input.move_left = 1;
    if (keycode == KEY_D)
        player->player_input.move_right = 1;
    if (keycode == KEY_LEFT)
        player->player_input.rotate_left = 1;
    if (keycode == KEY_RIGHT)
        player->player_input.rotate_right = 1;
    return (0);
}

int release_the_key(int keycode, void *param)
{
    t_game *game;
    t_player *player;

    game = (t_game *)param;
    player = game->player;
    if (keycode == KEY_ESC)
        close_the_window(param);
    if (keycode == KEY_W)
        player->player_input.move_forward = 0;
    if (keycode == KEY_S)
        player->player_input.move_backward = 0;
    if (keycode == KEY_A)
        player->player_input.move_left = 0;
    if (keycode == KEY_D)
        player->player_input.move_right = 0;
    if (keycode == KEY_LEFT)
        player->player_input.rotate_left = 0;
    if (keycode == KEY_RIGHT)
        player->player_input.rotate_right = 0;
    return (0);
}

int close_the_window(void *param)
{
    t_game *game;

    game = (t_game *)param;
    free_all(game);
    exit(0);
    return (0);
}

void init_keys(t_game *game)
{
    t_player *player;

    player = game->player;
    player->player_input.move_forward = 0;
    player->player_input.move_backward = 0;
    player->player_input.move_left = 0;
    player->player_input.move_right = 0;
    player->player_input.rotate_left = 0;
    player->player_input.rotate_right = 0;
}