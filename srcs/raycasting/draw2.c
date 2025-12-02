/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:49:39 by camerico          #+#    #+#             */
/*   Updated: 2025/12/02 14:57:25 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_wall_tx(t_game *g, t_ray *r, t_tex *t)
{
	double	pos;

	if (r->side == 0)
		pos = g->py + r->perp * r->ray_y;
	else
		pos = g->px + r->perp * r->ray_x;
	pos *= t->i.w;
	pos = fmod(pos, t->i.w);
	if ((r->side == 0 && r->ray_x > 0)
		|| (r->side == 1 && r->ray_y < 0))
		pos = t->i.w - pos - 1;
	return ((int)pos);
}

void	draw_walls(t_game *g, int x, t_ray *r, t_tex *tex)
{
	int		h;
	int		y;
	int		tx;
	double	step;
	double	ty;

	h = (int)((double)H / fmax(r->perp, 0.00001));
	if (h < 1)
		h = 1;
	y = -h / 2 + H / 2;
	ty = 0;
	if (y < 0)
	{
		ty = (-y) * ((double)tex->i.h / h);
		y = 0;
	}
	step = (double)tex->i.h / h;
	tx = get_wall_tx(g, r, tex);
	while (y < H && y < H / 2 + h / 2)
	{
		put_px(&g->frame, x, y,
			get_texel(tex, tx, (int)ty));
		ty += step;
		y++;
	}
}
