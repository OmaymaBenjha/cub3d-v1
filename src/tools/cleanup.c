#include "cub3d.h"

int    handle_exit(t_game *game)
{
    mlx_destroy_image(game->mlx_ptr, game->img_buffer.img_ptr);

    mlx_destroy_image(game->mlx_ptr, game->tex_east.img_ptr);
    mlx_destroy_image(game->mlx_ptr, game->tex_west.img_ptr);
    mlx_destroy_image(game->mlx_ptr, game->tex_north.img_ptr);
    mlx_destroy_image(game->mlx_ptr, game->tex_south.img_ptr);

    mlx_destroy_image(game->mlx_ptr, game->menu.bg.img_ptr);
    mlx_destroy_image(game->mlx_ptr, game->menu.btn_exit.img_ptr);
    mlx_destroy_image(game->mlx_ptr, game->menu.btn_start.img_ptr);
    mlx_destroy_image(game->mlx_ptr, game->tex_door.img_ptr);
    for (int i = 0; i < TORCH_FRAMES; i++)
        mlx_destroy_image(game->mlx_ptr, game->menu.torch[i].img_ptr);
    mlx_destroy_window(game->mlx_ptr, game->win_ptr);
    mlx_destroy_display(game->mlx_ptr);
    free(game->mlx_ptr);
    gc_freed();
    exit(0);
    return (0);
}