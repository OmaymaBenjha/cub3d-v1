#include "cub3d.h"

unsigned    int get_tex_color(t_img *tex, int x, int y)
{
    char    *dst;
    if (x < 0)
        x = 0;
    if (x >= tex->width)
        x = tex->width - 1;
    if (y < 0)
        y = 0;
    if (y >= tex->height)
        y = tex->height - 1;
    dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
    return (*(unsigned int *)dst);
}

static  void wall_and_tex_starting_pos(t_ray *ray, t_game *game,
        t_img **current_tex, double *wallX)
{
    ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
    ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
    if (ray->drawStart < 0)
        ray->drawStart = 0;
    ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
    if (ray->drawEnd >= HEIGHT)
        ray->drawEnd = HEIGHT - 1;
    if (ray->side == 0)
    {
        (*wallX) = game->p.posY + ray->perpWallDist * ray->rayDirY;
        if (ray->rayDirX > 0)
            *current_tex = &game->tex_east;
        else
            *current_tex = &game->tex_west;
    }
    else
    {
        (*wallX) = game->p.posX + ray->perpWallDist * ray->rayDirX;
        if (ray->rayDirY > 0)
            *current_tex = &game->tex_south;
        else 
            *current_tex = &game->tex_north;
    }
    (*wallX) -= floor(*wallX);
}

static  void draw_wall_pix(t_wall *wall, double step, t_img *current_img)
{
        if (wall->texPos >= current_img->height)
            wall->texPos = 0;
        wall->texY = (int)wall->texPos % current_img->height;
        wall->texPos += step;
        wall->color = get_tex_color(current_img, wall->texX, wall->texY);
}

void drawing_engin(t_ray *ray, t_game *game, int x)
{
    int     y;
    t_img   *current_tex;
    double  wallX;
    double  step;
    t_wall  wall;
    
    current_tex = NULL;
    wall_and_tex_starting_pos(ray, game, &current_tex, &wallX);
    wall.texX = (int)(wallX * (double)current_tex->width);
    if (ray->side == 0 && ray->rayDirX > 0)
        wall.texX = current_tex->width - wall.texX - 1;
    if (ray->side == 1 && ray->rayDirY < 0)
        wall.texX = current_tex->width - wall.texX - 1;
    step = 1.0 * current_tex->height / ray->lineHeight;
    wall.texPos = (ray->drawStart - HEIGHT / 2 + ray->lineHeight / 2) * step;
    y = -1;
    while (++y < ray->drawStart)
        my_mlx_pixel_put(&game->img_buffer, x, y, game->config.c_color.rgb);
    while (++y < ray->drawEnd)
    {
        draw_wall_pix(&wall, step, current_tex);
        my_mlx_pixel_put(&game->img_buffer, x, y, wall.color);
    }
    while (++y < HEIGHT)
        my_mlx_pixel_put(&game->img_buffer, x, y, game->config.f_color.rgb);
}
