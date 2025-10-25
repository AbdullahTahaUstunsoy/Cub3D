#include "../includes/cube3D.h"

int press_the_key(int keycode, void *param)
{
    t_game	*game;

    game = (t_game *)param;
    if (keycode == KEY_ESC)
        close_the_window(param);
    if (keycode == KEY_W)
        game->player->move_forward = 1;
    if (keycode == KEY_S)
        game->player->move_backward = 1;
    if (keycode == KEY_A)
        game->player->move_left = 1;
    if (keycode == KEY_D)
        game->player->move_right = 1;
    if (keycode == KEY_LEFT)
        game->player->rotate_left = 1;
    if (keycode == KEY_RIGHT)
        game->player->rotate_right = 1;
    return (0);
}

int release_the_key(int keycode, void *param)
{
    t_game	*game;

    game = (t_game *)param;
    if (keycode == KEY_ESC)
        close_the_window(param);
    if (keycode == KEY_W)
        game->player->move_forward = 0;
    if (keycode == KEY_S)
        game->player->move_backward = 0;
    if (keycode == KEY_A)
        game->player->move_left = 0;
    if (keycode == KEY_D)
        game->player->move_right = 0;
    if (keycode == KEY_LEFT)
        game->player->rotate_left = 0;
    if (keycode == KEY_RIGHT)
        game->player->rotate_right = 0;
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
	game->player->move_forward = 0;
	game->player->move_backward = 0;
	game->player->move_left = 0;
	game->player->move_right = 0;
	game->player->rotate_left = 0;
	game->player->rotate_right = 0;
}