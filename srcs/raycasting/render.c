#include "cub3D.h"

void	render_frame(t_game *g)
{
	int		x;
	t_ray	r;

	x = 0;
	while (x < W)
	{
		ray_setup(g, &r, x);
		ray_dda(g, &r);
		draw_column(g, x, &r);
		x++;
	}
	minimap_draw(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
}
