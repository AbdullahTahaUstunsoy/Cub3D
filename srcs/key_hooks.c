#include "../includes/cube3D.h"

int press_the_key(int keycode, void *param)
{
    t_player	*player;

    player = (t_player *)param;
    if (keycode == KEY_ESC)
        close_the_window(param);
    if (keycode == KEY_W)
        player->move_forward = 1;
    if (keycode == KEY_S)
        player->move_backward = 1;
    if (keycode == KEY_A)
        player->move_left = 1;
    if (keycode == KEY_D)
        player->move_right = 1;
    if (keycode == KEY_LEFT)
        player->rotate_left = 1;
    if (keycode == KEY_RIGHT)
        player->rotate_right = 1;
    return (0);
}

int release_the_key(int keycode, void *param)
{
    t_player	*player;

    player = (t_player *)param;
    if (keycode == KEY_ESC)
        close_the_window(param);
    if (keycode == KEY_W)
        player->move_forward = 0;
    if (keycode == KEY_S)
        player->move_backward = 0;
    if (keycode == KEY_A)
        player->move_left = 0;
    if (keycode == KEY_D)
        player->move_right = 0;
    if (keycode == KEY_LEFT)
        player->rotate_left = 0;
    if (keycode == KEY_RIGHT)
        player->rotate_right = 0;
    return (0);
}

int close_the_window(void *param) //free vs ekle
{
    (void)param;
    exit(0);
    return (0);
}

