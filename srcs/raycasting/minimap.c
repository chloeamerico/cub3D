/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 18:00:00 by user              #+#    #+#             */
/*   Updated: 2025/12/02 14:27:19 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

#define MM_R 8
#define MM_T 6
#define MM_OX 8
#define MM_OY 8


typedef struct s_mm_cell
{
	int			gx;
	int			gy;
	int			mx;
	int			my;
	int			sx;
	int			sy;
	uint32_t	col;
}	t_mm_cell;

// static void	mm_safe_px(t_game *g, int x, int y, uint32_t col)
// {
// 	if (x >= 0 && y >= 0 && x < W && y < H)
// 		put_px(&g->frame, x, y, col);
// }

// static void	mm_draw_rect(t_game *g, t_mm_rect r, uint32_t col)
// {
// 	int			i;
// 	int			j;

// 	j = 0;
// 	while (j < r.h)
// 	{
// 		i = 0;
// 		while (i < r.w)
// 		{
// 			mm_safe_px(g, r.x + i, r.y + j, col);
// 			i++;
// 		}
// 		j++;
// 	}
// }

// static void	mm_draw_circle(t_game *g, t_mm_circle c)
// {
// 	int			x;
// 	int			y;

// 	y = -c.r;
// 	while (y <= c.r)
// 	{
// 		x = -c.r;
// 		while (x <= c.r)
// 		{
// 			if (x * x + y * y <= c.r * c.r)
// 				mm_safe_px(g, c.x + x, c.y + y, c.col);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void	mm_draw_dir(t_game *g, t_mm_dir d)
// {
// 	double		x;
// 	double		y;
// 	int			i;

// 	x = (double)d.x;
// 	y = (double)d.y;
// 	i = 0;
// 	while (i < d.len)
// 	{
// 		mm_safe_px(g, (int)x, (int)y, d.col);
// 		x += g->dir_x;
// 		y += g->dir_y;
// 		i++;
// 	}
// }

static void	mm_draw_bg(t_game *g)
{
	t_mm_rect	r;

	r.x = MM_OX - 2;
	r.y = MM_OY - 2;
	r.w = (2 * MM_R + 1) * MM_T + 4;
	r.h = (2 * MM_R + 1) * MM_T + 4;
	mm_draw_rect(g, r, 0x80000000);
}

static void	mm_draw_cell_line(t_game *g, int gy)
{
	t_mm_cell	c;
	t_mm_rect	r;

	c.gy = gy;
	c.gx = -MM_R;
	while (c.gx <= MM_R)
	{
		c.mx = (int)g->px + c.gx;
		c.my = (int)g->py + c.gy;
		c.sx = MM_OX + (c.gx + MM_R) * MM_T;
		c.sy = MM_OY + (c.gy + MM_R) * MM_T;
		if (c.mx < 0 || c.my < 0 || c.mx >= g->map_w || c.my >= g->map_h)
			c.col = 0xFF202020;
		else if (g->map_int[c.my][c.mx] == 1)
			c.col = 0xFF505050;
		else
			c.col = 0xFF9A9A9A;
		r.x = c.sx;
		r.y = c.sy;
		r.w = MM_T - 1;
		r.h = MM_T - 1;
		mm_draw_rect(g, r, c.col);
		c.gx++;
	}
}

static void	mm_draw_cells(t_game *g)
{
	int			gy;

	gy = -MM_R;
	while (gy <= MM_R)
	{
		mm_draw_cell_line(g, gy);
		gy++;
	}
}

static void	mm_draw_player(t_game *g)
{
	t_mm_circle	c;
	t_mm_dir	d;
	int			pcx;
	int			pcy;

	pcx = MM_OX + MM_R * MM_T;
	pcx += (int)((g->px - floor(g->px)) * MM_T);
	pcy = MM_OY + MM_R * MM_T;
	pcy += (int)((g->py - floor(g->py)) * MM_T);
	c.x = pcx;
	c.y = pcy;
	c.r = 2;
	c.col = 0xFFFF0000;
	mm_draw_circle(g, c);
	d.x = pcx;
	d.y = pcy;
	d.len = 8;
	d.col = 0xFFFF0000;
	mm_draw_dir(g, d);
}

void	minimap_draw(t_game *g)
{
	mm_draw_bg(g);
	mm_draw_cells(g);
	mm_draw_player(g);
}
