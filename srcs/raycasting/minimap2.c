/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:21:02 by camerico          #+#    #+#             */
/*   Updated: 2025/12/08 12:25:49 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Dessine un cercle rempli
void	mm_draw_circle(t_game *g, t_mm_circle c)
{
	int			x;
	int			y;

	y = -c.r;
	while (y <= c.r)
	{
		x = -c.r;
		while (x <= c.r)
		{
			if (x * x + y * y <= c.r * c.r)
				safescreen_mm(g, c.x + x, c.y + y, c.col);
			x++;
		}
		y++;
	}
}

// Dessine la flèche de direction
void	direction_mm(t_game *g, t_mm_dir d)
{
	double		x;
	double		y;
	int			i;

	x = (double)d.x;
	y = (double)d.y;
	i = 0;
	while (i < d.len)
	{
		safescreen_mm(g, (int)x, (int)y, d.col);
		x += g->dir_x;
		y += g->dir_y;
		i++;
	}
}

// Sécurise l’écriture d’un pixel
void	safescreen_mm(t_game *g, int x, int y, uint32_t col)
{
	if (x >= 0 && y >= 0 && x < W && y < H)
		put_px(&g->frame, x, y, col);
}

// Dessine un rectangle plein
void	mm_draw_rect(t_game *g, t_mm_rect r, uint32_t col)
{
	int			i;
	int			j;

	j = 0;
	while (j < r.h)
	{
		i = 0;
		while (i < r.w)
		{
			safescreen_mm(g, r.x + i, r.y + j, col);
			i++;
		}
		j++;
	}
}
