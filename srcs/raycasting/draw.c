/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 14:57:49 by lleichtn          #+#    #+#             */
/*   Updated: 2025/12/04 16:03:29 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

// void	draw_walls(t_game *g, int x, t_ray *r, t_tex *tex)
// {
// 	int		h;
// 	int		y;
// 	int		tx;
// 	double	step;
// 	double	ty;

// 	h = (int)((double)H / fmax(r->perp, 0.00001));
// 	if (h < 1)
// 		h = 1;
// 	y = -h / 2 + H / 2;
// 	ty = 0;
// 	if (y < 0)
// 	{
// 		ty = (-y) * ((double)tex->i.h / h);
// 		y = 0;
// 	}
// 	step = (double)tex->i.h / h;
// 	tx = get_wall_tx(g, r, tex);
// 	while (y < H && y < H / 2 + h / 2)
// 	{
// 		put_px(&g->frame, x, y,
// 			get_texel(tex, tx, (int)ty));
// 		ty += step;
// 		y++;
// 	}
// }

// static void	draw_floor_column(t_game *g, int x, t_ray *r, int floor_begin)
// {
// 	double	wallx;
// 	double	floorxwall;
// 	double	floorywall;
// 	int		y;

// 	if (floor_begin < 0)
// 		floor_begin = 0;
// 	if (r->side == 0)
// 		wallx = g->py + r->perp * r->ray_y;
// 	else
// 		wallx = g->px + r->perp * r->ray_x;
// 	wallx -= floor(wallx);
// 	if (r->side == 0 && r->ray_x > 0)
// 	{
// 		floorxwall = r->map_x;
// 		floorywall = r->map_y + wallx;
// 	}
// 	else if (r->side == 0 && r->ray_x < 0)
// 	{
// 		floorxwall = r->map_x + 1.0;
// 		floorywall = r->map_y + wallx;
// 	}
// 	else if (r->side == 1 && r->ray_y > 0)
// 	{
// 		floorxwall = r->map_x + wallx;
// 		floorywall = r->map_y;
// 	}
// 	else
// 	{
// 		floorxwall = r->map_x + wallx;
// 		floorywall = r->map_y + 1.0;
// 	}
// 	y = floor_begin;
// 	while (y < H)
// 	{
// 		double curDist = (double)H / (2.0 * y - H + 0.00001);
// 		double w = curDist / fmax(r->perp, 1e-6);
// 		double curX = w * floorxwall + (1.0 - w) * g->px;
// 		double curY = w * floorywall + (1.0 - w) * g->py;
// 		int tx = (int)(curX * g->floor_tex.i.w) % g->floor_tex.i.w;
// 		int ty = (int)(curY * g->floor_tex.i.h) % g->floor_tex.i.h;
// 		if (tx < 0)
// 			tx += g->floor_tex.i.w;
// 		if (ty < 0)
// 			ty += g->floor_tex.i.h;
// 		put_px(&g->frame, x, y, get_texel(&g->floor_tex, tx, ty));
// 		y++;
// 	}
// }

typedef struct s_floor_ctx
{
	double	fx;
	double	fy;
	int		y;
}	t_floor_ctx;

// static void	floor_wall_pos(t_ray *r, double wall_x,
// 			double *floor_x, double *floor_y)
// {
// 	if (r->side == 0 && r->ray_x > 0)
// 	{
// 		*floor_x = r->map_x;
// 		*floor_y = r->map_y + wall_x;
// 	}
// 	else if (r->side == 0 && r->ray_x < 0)
// 	{
// 		*floor_x = r->map_x + 1.0;
// 		*floor_y = r->map_y + wall_x;
// 	}
// 	else if (r->side == 1 && r->ray_y > 0)
// 	{
// 		*floor_x = r->map_x + wall_x;
// 		*floor_y = r->map_y;
// 	}
// 	else
// 	{
// 		*floor_x = r->map_x + wall_x;
// 		*floor_y = r->map_y + 1.0;
// 	}
// }

// static void	floor_tex_loop(t_game *g, int x, t_ray *r, t_floor_ctx c)
// {
// 	double	cur_dist;
// 	double	w;
// 	double	cur_x;
// 	double	cur_y;
// 	int		tx;
// 	int		ty;

// 	while (c.y < H)
// 	{
// 		cur_dist = (double)H / (2.0 * c.y - H + 0.00001);
// 		w = cur_dist / fmax(r->perp, 1e-6);
// 		cur_x = w * c.fx + (1.0 - w) * g->px;
// 		cur_y = w * c.fy + (1.0 - w) * g->py;
// 		tx = (int)(cur_x * g->floor_tex.i.w) % g->floor_tex.i.w;
// 		ty = (int)(cur_y * g->floor_tex.i.h) % g->floor_tex.i.h;
// 		if (tx < 0)
// 			tx += g->floor_tex.i.w;
// 		if (ty < 0)
// 			ty += g->floor_tex.i.h;
// 		put_px(&g->frame, x, c.y,
// 			get_texel(&g->floor_tex, tx, ty));
// 		c.y++;
// 	}
// }

// static void	floor_tex_loop(t_game *g, int x, t_ray *r, t_floor_ctx c)
// {
// 	double	dist;
// 	double	w;
// 	double	cur_x;
// 	double	cur_y;
// 	int		tex[2];

// 	while (c.y < H)
// 	{
// 		dist = (double)H / (2.0 * c.y - H + 0.00001);
// 		w = dist / fmax(r->perp, 1e-6);
// 		cur_x = w * c.fx + (1.0 - w) * g->px;
// 		cur_y = w * c.fy + (1.0 - w) * g->py;
// 		tex[0] = (int)(cur_x * g->floor_tex.i.w) % g->floor_tex.i.w;
// 		tex[1] = (int)(cur_y * g->floor_tex.i.h) % g->floor_tex.i.h;
// 		if (tex[0] < 0)
// 			tex[0] += g->floor_tex.i.w;
// 		if (tex[1] < 0)
// 			tex[1] += g->floor_tex.i.h;
// 		put_px(&g->frame, x, c.y,
// 			get_texel(&g->floor_tex, tex[0], tex[1]));
// 		c.y++;
// 	}
// }

// static void	draw_floor_column(t_game *g, int x, t_ray *r, int floor_begin)
// {
// 	double		wall_x;
// 	t_floor_ctx	c;

// 	if (floor_begin < 0)
// 		floor_begin = 0;
// 	if (r->side == 0)
// 		wall_x = g->py + r->perp * r->ray_y;
// 	else
// 		wall_x = g->px + r->perp * r->ray_x;
// 	wall_x -= floor(wall_x);
// 	floor_wall_pos(r, wall_x, &c.fx, &c.fy);
// 	c.y = floor_begin;
// 	floor_tex_loop(g, x, r, c);
// }

void	draw_column(t_game *g, int x, t_ray *r)
{
	int		line_h;
	int		ceil_end;
	int		floor_begin;
	t_span	s;
	t_tex	*tex;

	line_h = (int)((double)H / fmax(r->perp, 1e-6));
	tex = choose_texture(g, r);
	ceil_end = -line_h / 2 + H / 2 - 1;
	floor_begin = line_h / 2 + H / 2;
	s.y0 = 0;
	s.y1 = ceil_end;
	draw_span(g, x, s, g->ceil_color);
	draw_walls(g, x, r, tex);
	if (floor_begin < H)
	{
	    t_span s;
	    s.y0 = floor_begin;
	    s.y1 = H - 1;
	    draw_span(g, x, s, g->floor_color);
	}
}
