#include "cub3d.h"
static void draw_btn_loop(t_game *game, t_img img, t_rect rect, double sc_x, double sc_y)
{
    int tex_x;
    int tex_y;
    unsigned int color;
    int x;
    int y;

    x = rect.x - 1;
    while (++x < (rect.x + rect.width))
    {
        y = rect.y - 1;
        while (++y < (rect.y + rect.height))
        {
            tex_x = (int)((x - rect.x) * sc_x);
            tex_y = (int)((y - rect.y) * sc_y);
            if (tex_x >= img.width)
                tex_x = img.width - 1;
            if (tex_y >= img.height)
                tex_y = img.height - 1;
            color = get_tex_color(&img, tex_x, tex_y);
            if (color != 0xFF000000 && color != 0x000000) 
                my_mlx_pixel_put(&game->img_buffer, x, y, color);
        }
    }
}
static void draw_btn(t_game *game, t_img *img, t_rect *rect)
{
    double  sc_x;
    double  sc_y;

    sc_x = (double)img->width / rect->width;
    sc_y = (double)img->height / rect->height;
    draw_btn_loop(game, *img, *rect, sc_x, sc_y);
}
int check_mouse_event_bound(t_game *game, t_rect rect)
{
    if (game->mouse_x >= rect.x && 
        game->mouse_x <= (rect.x + rect.width) &&
        game->mouse_y >= rect.y && 
        game->mouse_y <= (rect.y + rect.height))
        return (1);
    else
        return (0);
    
}
void    render_welcome_page(t_game *game)
{
    int     x;
    int     y;
    int     color;
    double  sc_x;
    double  sc_y;
    int     tex_x;
    int     tex_y;

    x = 0;
    sc_x = (double)game->menu.bg.width / WIDTH;
    sc_y = (double)game->menu.bg.height / HEIGHT;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            tex_x = (int)(x * sc_x);
            tex_y = (int)(y * sc_y);
            if (tex_x >= game->menu.bg.width)
                tex_x = game->menu.bg.width - 1;
            if (tex_y >= game->menu.bg.height)
                tex_y = game->menu.bg.height - 1;
            color = get_tex_color(&game->menu.bg, tex_x, tex_y);
            my_mlx_pixel_put(&game->img_buffer, x, y, color);
            y++;
        }
        x++;
    }
    t_rect draw_start = game->menu.start_rect;
    t_rect draw_exit = game->menu.exit_rect;
    int pop = 10;
    if (check_mouse_event_bound(game, game->menu.start_rect))
    {
        draw_start.x -= pop;
        draw_start.y -= pop;
        draw_start.width += (pop * 3);
        draw_start.height += (pop * 3);        
    }
    if (check_mouse_event_bound(game, game->menu.exit_rect))
    {
        draw_exit.x -= pop;
        draw_exit.y -= pop;
        draw_exit.width += (pop * 3);
        draw_exit.height += (pop * 3);        
    }
    draw_btn(game, &game->menu.btn_start, &draw_start);
    draw_btn(game, &game->menu.btn_exit, &draw_exit);
}
