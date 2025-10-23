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

    printf("Cleaning up images and exiting...\n");

    // 1. Ana render imajını yok et
    // (Bu imajı main'de sadece 1 kez oluşturduğunu varsayıyorum)
    if (game->img.img)
        mlx_destroy_image(game->mlx, game->img.img);

    // 2. Dört adet texture imajını yok et
    // (Bunları da load_textures'da sadece 1 kez oluşturdun)
    if (game->textures[0].img)
        mlx_destroy_image(game->mlx, game->textures[0].img);
    if (game->textures[1].img)
        mlx_destroy_image(game->mlx, game->textures[1].img);
    if (game->textures[2].img)
        mlx_destroy_image(game->mlx, game->textures[2].img);
    if (game->textures[3].img)
        mlx_destroy_image(game->mlx, game->textures[3].img);

    // 3. Pencereyi yok et
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);

    // 4. MLX display'i yok et (Linux için)
    // mlx_destroy_display(game->mlx);
    
    // 5. Kalan hafızayı free et
    // (map->map, player, ray, game, vb. free fonksiyonlarını buraya ekle)
    // free_map(game->map);
    // free(game->player);
    // free(game->ray);
    // free(game->mlx); // Display'i free ettikten sonra
    // free(game);

    // En son programdan çık
    exit(0);
    return (0);
}
