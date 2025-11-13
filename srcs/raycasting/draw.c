/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:57:49 by lleichtn          #+#    #+#             */
/*   Updated: 2025/11/13 15:13:57 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// static void	draw_span(t_game *g, int x, int y0, int y1, uint32_t c)
// {
// 	if (y0 < 0)
// 		y0 = 0;
// 	if (y1 >= H)
// 		y1 = H - 1;
// 	while (y0 <= y1)
// 	{
// 		put_px(&g->frame, x, y0, c);
// 		y0++;
// 	}
// }

typedef struct s_span
{
	int	y0;
	int	y1;
}	t_span;

void	draw_span(t_game *g, int x, t_span s, uint32_t col)
{
	if (s.y0 < 0)
		s.y0 = 0;
	if (s.y1 >= H)
		s.y1 = H - 1;
	while (s.y0 <= s.y1)
	{
		put_px(&g->frame, x, s.y0, col);
		s.y0++;
	}
}

static void	draw_walls(t_game *g, int x, t_ray *r, int h, int tex_id)
{
	int		y;
	double	step;
	double	tex_pos;
	int		ty;
	int		tx;

	if (h < 1)
		h = 1;
	y = -h / 2 + H / 2;
	tex_pos = 0.0;
	if (y < 0)
	{
		tex_pos = (-y) * (double)g->tex[tex_id].i.h / h;
		y = 0;
	}
	step = (double)g->tex[tex_id].i.h / (double)h;
	if (r->side == 0)
		tx = (int)((g->py + r->perp * r->ray_y) * g->tex[tex_id].i.w) % g->tex[tex_id].i.w;
	else
		tx = (int)((g->px + r->perp * r->ray_x) * g->tex[tex_id].i.w) % g->tex[tex_id].i.w;
	if ((r->side == 0 && r->ray_x > 0) || (r->side == 1 && r->ray_y < 0))
		tx = g->tex[tex_id].i.w - 1 - tx;
	while (y < H / 2 + h / 2 && y < H)
	{
		ty = (int)tex_pos;
		put_px(&g->frame, x, y, get_texel(&g->tex[tex_id], tx, ty));
		tex_pos += step;
		y++;
	}
}

static void	draw_floor_column(t_game *g, int x, t_ray *r, int floor_begin)
{
	double	wallx;
	double	floorxwall;
	double	floorywall;
	int		y;

	if (floor_begin < 0)
		floor_begin = 0;
	if (r->side == 0)
		wallx = g->py + r->perp * r->ray_y;
	else
		wallx = g->px + r->perp * r->ray_x;
	wallx -= floor(wallx);
	if (r->side == 0 && r->ray_x > 0)
	{
		floorxwall = r->map_x;
		floorywall = r->map_y + wallx;
	}
	else if (r->side == 0 && r->ray_x < 0)
	{
		floorxwall = r->map_x + 1.0;
		floorywall = r->map_y + wallx;
	}
	else if (r->side == 1 && r->ray_y > 0)
	{
		floorxwall = r->map_x + wallx;
		floorywall = r->map_y;
	}
	else
	{
		floorxwall = r->map_x + wallx;
		floorywall = r->map_y + 1.0;
	}
	y = floor_begin;
	while (y < H)
	{
		double curDist = (double)H / (2.0 * y - H + 0.00001);
		double w = curDist / fmax(r->perp, 1e-6);
		double curX = w * floorxwall + (1.0 - w) * g->px;
		double curY = w * floorywall + (1.0 - w) * g->py;
		int tx = (int)(curX * g->floor_tex.i.w) % g->floor_tex.i.w;
		int ty = (int)(curY * g->floor_tex.i.h) % g->floor_tex.i.h;
		if (tx < 0)
			tx += g->floor_tex.i.w;
		if (ty < 0)
			ty += g->floor_tex.i.h;
		put_px(&g->frame, x, y, get_texel(&g->floor_tex, tx, ty));
		y++;
	}
}

void	draw_column(t_game *g, int x, t_ray *r)
{
	int		line_h;
	int		tex_id;
	int		ceil_end;
	int		floor_begin;
	t_span s;

	line_h = (int)((double)H / fmax(r->perp, 1e-6));
	tex_id = choose_tex_id(r);
	ceil_end = -line_h / 2 + H / 2 - 1;
	floor_begin = line_h / 2 + H / 2;
	// draw_span(g, x, 0, ceil_end, g->ceil_col);
	s.y0 = 0;
	s.y1 = ceil_end;
	draw_span(g, x, s, g->ceil_col);
	draw_walls(g, x, r, line_h, tex_id);
	if (floor_begin < H)
		draw_floor_column(g, x, r, floor_begin);
}
