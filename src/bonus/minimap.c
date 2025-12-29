#include "cub3d_bonus.h"
static void	put_pixel(t_textures *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void    draw_mp(t_game *g)
{
    int x;
    int y;
    int mx;
    int my;

    y = -1;
    while (y++ < MINI_H)
    {
        x = -1;
        while (x++ < MINI_W)
        {
            mx = (int)g->p.pos_x + ((x - MINI_W / 2.0) / MINI_TILE);
            my = (int)g->p.pos_y + ((y - MINI_H / 2.0) / MINI_TILE);
            if (mx < 0 || my < 0|| my >= (int)g->map_height|| mx >= (int)g->map_width)
				put_pixel(&g->img_buffer, x + 30, y + 30, COLOR_VOID);
			else if (g->map[my][mx] == '1')
				put_pixel(&g->img_buffer, x + 30, y + 30, COLOR_WALL);
			else if (g->map[my][mx] == 'D' || g->map[my][mx] == 'O')
				put_pixel(&g->img_buffer, x + 30, y + 30, COLOR_DOOR);
			else if (g->map[my][mx] == '0')
				put_pixel(&g->img_buffer, x + 30, y + 30, COLOR_FLOOR);
			else
				put_pixel(&g->img_buffer, x + 30, y + 30, COLOR_VOID);
        }  
    }
}
static void	draw_p(t_game *g)
{
	int	cx;
	int	cy;
	int	i;
	int	j;

	cx = (MINI_W / 2) + 35;
	cy = (MINI_H / 2) + 35;
	i = -3;
	while (i <= 3)
	{
		j = -3;
		while (j <= 3)
		{
			put_pixel(&g->img_buffer, cx + i, cy + j, COLOR_PLAYER);
			j++;
		}
		i++;
	}
}

static void	draw_pd(t_game *g)
{
	int		i;
	double	x;
	double	y;

	i = 0;
	while (i < 15)
	{
		x = (MINI_W / 2) + 35 + g->p.dir_x * i;
		y = (MINI_H / 2) + 35 + g->p.dir_y * i;
		put_pixel(&g->img_buffer, (int)x, (int)y, COLOR_DIR);
		i++;
	}
}

void    render_minimap(t_game *g)
{
    draw_mp(g);
    draw_p(g);
    draw_pd(g);
}