#include "cub3d.h"

#define TILE_SIZE 30 // Size of each block in pixels

static void    my_mlx_pixel_put(t_textures *data, int x, int y, int color)
{
    char    *dst;

    if (x < 0 || x >= 800 || y < 0 || y >= 800)
        return;
    dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}


// 1. Raycasting Logic
static void    raycasting(t_game *game)
{
    int     x;
    t_ray   ray;

    x = 0;
    while (x < 800) // Loop through every vertical column of pixels
    {
        // --- Init Ray ---
        ray.cameraX = 2 * x / (double)800 - 1;
        ray.rayDirX = game->player.dirX + game->player.planeX * ray.cameraX;
        ray.rayDirY = game->player.dirY + game->player.planeY * ray.cameraX;

        ray.mapX = (int)game->player.posX;
        ray.mapY = (int)game->player.posY;

        ray.deltaDistX = fabs(1 / ray.rayDirX);
        ray.deltaDistY = fabs(1 / ray.rayDirY);
        ray.hit = 0;

        // --- Step Calculation ---
        if (ray.rayDirX < 0)
        {
            ray.stepX = -1;
            ray.sideDistX = (game->player.posX - ray.mapX) * ray.deltaDistX;
        }
        else
        {
            ray.stepX = 1;
            ray.sideDistX = (ray.mapX + 1.0 - game->player.posX) * ray.deltaDistX;
        }
        if (ray.rayDirY < 0)
        {
            ray.stepY = -1;
            ray.sideDistY = (game->player.posY - ray.mapY) * ray.deltaDistY;
        }
        else
        {
            ray.stepY = 1;
            ray.sideDistY = (ray.mapY + 1.0 - game->player.posY) * ray.deltaDistY;
        }

        // --- DDA Loop (Find Wall) ---
        while (ray.hit == 0)
        {
            if (ray.sideDistX < ray.sideDistY)
            {
                ray.sideDistX += ray.deltaDistX;
                ray.mapX += ray.stepX;
                ray.side = 0; // East/West wall
            }
            else
            {
                ray.sideDistY += ray.deltaDistY;
                ray.mapY += ray.stepY;
                ray.side = 1; // North/South wall
            }
            // Check if we hit a wall '1'
            if (game->map[ray.mapY][ray.mapX] == '1')
                ray.hit = 1;
        }
        if (ray.side == 0)
            ray.perpWallDist = (ray.sideDistX - ray.deltaDistX);
        else
            ray.perpWallDist = (ray.sideDistY - ray.deltaDistY);

        ray.lineHeight = (int)(800 / ray.perpWallDist);

        ray.drawStart = -ray.lineHeight / 2 + 800 / 2;
        if (ray.drawStart < 0) ray.drawStart = 0;
        
        ray.drawEnd = ray.lineHeight / 2 + 800 / 2;
        if (ray.drawEnd >= 800) ray.drawEnd = 800 - 1;
        int y = 0;
        while (y < ray.drawStart)
        {
            my_mlx_pixel_put(&game->img_buffer, x, y, game->config.c_color.rgb);
            y++;
        }
        int color = (ray.side == 1) ? 0x00FF0000 : 0x00AABBCC; // Red vs Blueish
        while (y < ray.drawEnd)
        {
            my_mlx_pixel_put(&game->img_buffer, x, y, color);
            y++;
        }
        while (y < 800)
        {
            my_mlx_pixel_put(&game->img_buffer, x, y, game->config.f_color.rgb);
            y++;
        }
        x++;
    }
}

static int render_frame(t_game *game)
{
    raycasting(game);
    mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img_buffer.img_ptr, 0, 0);
    return (0);
}

void    init_game(t_game *game)
{
    game->mlx_ptr = mlx_init();
    game->win_ptr = mlx_new_window(game->mlx_ptr, 800, 800, "cub3d");
    game->img_buffer.img_ptr = mlx_new_image(game->mlx_ptr, 800, 800);
    game->img_buffer.addr = mlx_get_data_addr(game->img_buffer.img_ptr, 
        &game->img_buffer.bpp, &game->img_buffer.line_len, &game->img_buffer.endian);
    mlx_loop_hook(game->mlx_ptr, render_frame, game);
    mlx_hook(game->win_ptr, 2, 1L<<0, key_handler, game);
    mlx_hook(game->win_ptr, 17, 0, (void *)exit, 0);
    mlx_loop(game->mlx_ptr);
}