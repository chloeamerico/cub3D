/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:47:08 by lleichtn          #+#    #+#             */
/*   Updated: 2025/12/02 15:11:02 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	set_steps(t_ray *r, double px, double py)
{
	if (r->ray_x < 0)
	{
		r->step_x = -1;
		r->side_x = (px - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - px) * r->delta_x;
	}
	if (r->ray_y < 0)
	{
		r->step_y = -1;
		r->side_y = (py - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - py) * r->delta_y;
	}
}

static void	set_deltas(t_ray *r)
{
	if (r->ray_x == 0.0)
		r->delta_x = 1e30;
	else
		r->delta_x = fabs(1.0 / r->ray_x);
	if (r->ray_y == 0.0)
		r->delta_y = 1e30;
	else
		r->delta_y = fabs(1.0 / r->ray_y);
}

static void	ray_setup(t_game *g, t_ray *r, int x)
{
	r->cam_x = 2.0 * x / (double)W - 1.0;
	r->ray_x = g->dir_x + g->pl_x * r->cam_x;
	r->ray_y = g->dir_y + g->pl_y * r->cam_x;
	r->map_x = (int)g->px;
	r->map_y = (int)g->py;
	set_deltas(r);
	set_steps(r, g->px, g->py);
}

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
