/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:59:06 by camerico          #+#    #+#             */
/*   Updated: 2025/12/02 15:02:41 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	put_checker_px(t_tex *t, int x, int y)
{
	uint32_t	*px;
	int			cell;

	px = (uint32_t *)(t->i.addr
			+ y * t->i.line_len
			+ x * (t->i.bpp / 8));
	cell = (x / 8) + (y / 8);
	if (cell % 2)
		*px = 0xFF5555;
	else
		*px = 0xAAAAAA;
}

static void	gen_checker(t_game *g, t_tex *t, int w, int h)
{
	int	x;
	int	y;

	t->i.img = mlx_new_image(g->mlx, w, h);
	t->i.addr = mlx_get_data_addr(t->i.img, &t->i.bpp,
			&t->i.line_len, &t->i.endian);
	t->i.w = w;
	t->i.h = h;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			put_checker_px(t, x, y);
			x++;
		}
		y++;
	}
}

int	load_wall_textures(t_game *g)
{
	if (!load_one(g, &g->tex_no, g->config.no_texture))
		gen_checker(g, &g->tex_no, 64, 64);
	if (!load_one(g, &g->tex_so, g->config.so_texture))
		gen_checker(g, &g->tex_so, 64, 64);
	if (!load_one(g, &g->tex_we, g->config.we_texture))
		gen_checker(g, &g->tex_we, 64, 64);
	if (!load_one(g, &g->tex_ea, g->config.ea_texture))
		gen_checker(g, &g->tex_ea, 64, 64);
	return (1);
}

int	load_one(t_game *g, t_tex *t, const char *path)
{
	if (!path)
		return (0);
	t->i.img = mlx_xpm_file_to_image(g->mlx, (char *)path,
			&t->i.w, &t->i.h);
	if (!t->i.img)
		return (0);
	t->i.addr = mlx_get_data_addr(t->i.img, &t->i.bpp,
			&t->i.line_len, &t->i.endian);
	return (t->i.addr != NULL);
}
