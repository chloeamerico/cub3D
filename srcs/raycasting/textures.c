/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 15:55:29 by lleichtn          #+#    #+#             */
/*   Updated: 2025/12/02 13:05:28 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3D.h"

// static int	load_one(t_game *g, t_tex *t, const char *path)
// {
// 	t->i.img = mlx_xpm_file_to_image(g->mlx, (char *)path,
// 			&t->i.w, &t->i.h);
// 	if (!t->i.img)
// 		return (0);
// 	t->i.addr = mlx_get_data_addr(t->i.img, &t->i.bpp,
// 			&t->i.line_len, &t->i.endian);
// 	if (!t->i.addr)
// 		return (0);
// 	return (1);
// }

// static void	put_checker_px(t_tex *t, int x, int y)
// {
// 	uint32_t	*px;
// 	int			cell;

// 	px = (uint32_t *)(t->i.addr
// 			+ y * t->i.line_len
// 			+ x * (t->i.bpp / 8));
// 	cell = (x / 8) + (y / 8);
// 	if (cell % 2 == 1)
// 		*px = 0xFF5555;
// 	else
// 		*px = 0xAAAAAA;
// }

// static void	gen_checker(t_game *g, t_tex *t, int w, int h)
// {
// 	int	x;
// 	int	y;

// 	(void)g;
// 	t->i.img = mlx_new_image(g->mlx, w, h);
// 	t->i.addr = mlx_get_data_addr(t->i.img, &t->i.bpp,
// 			&t->i.line_len, &t->i.endian);
// 	t->i.w = w;
// 	t->i.h = h;
// 	y = 0;
// 	while (y < h)
// 	{
// 		x = 0;
// 		while (x < w)
// 		{
// 			put_checker_px(t, x, y);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// int	load_textures(t_game *g, t_pair ns, t_pair we)
// {
// 	if (!load_one(g, &g->tex[TEX_NO], ns.a))
// 		gen_checker(g, &g->tex[TEX_NO], 64, 64);
// 	if (!load_one(g, &g->tex[TEX_SO], ns.b))
// 		gen_checker(g, &g->tex[TEX_SO], 64, 64);
// 	if (!load_one(g, &g->tex[TEX_WE], we.a))
// 		gen_checker(g, &g->tex[TEX_WE], 64, 64);
// 	if (!load_one(g, &g->tex[TEX_EA], we.b))
// 		gen_checker(g, &g->tex[TEX_EA], 64, 64);
// 	return (1);
// }

// void	destroy_textures(t_game *g)
// {
// 	int	i;

// 	i = 0;
// 	while (i < TEX_NB)
// 	{
// 		if (g->tex[i].i.img)
// 			mlx_destroy_image(g->mlx, g->tex[i].i.img);
// 		i++;
// 	}
// }

// uint32_t	get_texel(const t_tex *t, int u, int v)
// {
// 	char	*p;

// 	if (u < 0)
// 		u = 0;
// 	if (v < 0)
// 		v = 0;
// 	if (u >= t->i.w)
// 		u = t->i.w - 1;
// 	if (v >= t->i.h)
// 		v = t->i.h - 1;
// 	p = t->i.addr
// 		+ v * t->i.line_len
// 		+ u * (t->i.bpp / 8);
// 	return (*(uint32_t *)p);
// }

// int	choose_tex_id(const t_ray *r)
// {
// 	if (r->side == 0)
// 	{
// 		if (r->ray_x < 0)
// 			return (TEX_WE);
// 		return (TEX_EA);
// 	}
// 	if (r->ray_y < 0)
// 		return (TEX_NO);
// 	return (TEX_SO);
// }

// static void	put_floor_px(t_tex *t, int x, int y)
// {
// 	uint32_t	*px;
// 	int			cell;

// 	px = (uint32_t *)(t->i.addr
// 			+ y * t->i.line_len
// 			+ x * (t->i.bpp / 8));
// 	cell = (x / 8) + (y / 8);
// 	if (cell % 2 == 1)
// 		*px = 0x3A6B2E;
// 	else
// 		*px = 0x2A4D1A;
// }

// static void	gen_floor_checker(t_game *g, t_tex *t, int w, int h)
// {
// 	int	x;
// 	int	y;

// 	(void)g;
// 	t->i.img = mlx_new_image(g->mlx, w, h);
// 	t->i.addr = mlx_get_data_addr(t->i.img, &t->i.bpp,
// 			&t->i.line_len, &t->i.endian);
// 	t->i.w = w;
// 	t->i.h = h;
// 	y = 0;
// 	while (y < h)
// 	{
// 		x = 0;
// 		while (x < w)
// 		{
// 			put_floor_px(t, x, y);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// int	load_floor_texture(t_game *g, const char *path)
// {
// 	if (!load_one(g, &g->floor_tex, path))
// 		gen_floor_checker(g, &g->floor_tex, 64, 64);
// 	return (1);
// }

#include "cub3D.h"

static int	load_one(t_game *g, t_tex *t, const char *path)
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

static void	put_checker_px(t_tex *t, int x, int y)
{
	uint32_t	*px;
	int			cell;

	px = (uint32_t *)(t->i.addr
			+ y * t->i.line_len
			+ x * (t->i.bpp / 8));
	cell = (x / 8) + (y / 8);
	*px = (cell % 2) ? 0xFF5555 : 0xAAAAAA;
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

void	destroy_textures(t_game *g)
{
	if (g->tex_no.i.img)
		mlx_destroy_image(g->mlx, g->tex_no.i.img);
	if (g->tex_so.i.img)
		mlx_destroy_image(g->mlx, g->tex_so.i.img);
	if (g->tex_we.i.img)
		mlx_destroy_image(g->mlx, g->tex_we.i.img);
	if (g->tex_ea.i.img)
		mlx_destroy_image(g->mlx, g->tex_ea.i.img);
	if (g->floor_tex.i.img)
		mlx_destroy_image(g->mlx, g->floor_tex.i.img);
}

uint32_t	get_texel(const t_tex *t, int u, int v)
{
	char	*p;

	if (u < 0)
		u = 0;
	if (v < 0)
		v = 0;
	if (u >= t->i.w)
		u = t->i.w - 1;
	if (v >= t->i.h)
		v = t->i.h - 1;
	p = t->i.addr
		+ v * t->i.line_len
		+ u * (t->i.bpp / 8);
	return (*(uint32_t *)p);
}

t_tex	*choose_texture(t_game *g, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_x < 0)
			return (&g->tex_we);
		return (&g->tex_ea);
	}
	if (r->ray_y < 0)
		return (&g->tex_no);
	return (&g->tex_so);
}

static void	put_floor_px(t_tex *t, int x, int y)
{
	uint32_t	*px;
	int			cell;

	px = (uint32_t *)(t->i.addr
			+ y * t->i.line_len
			+ x * (t->i.bpp / 8));
	cell = (x / 8) + (y / 8);
	if (cell % 2 == 1)
		*px = 0x3A6B2E;
	else
		*px = 0x2A4D1A;
}

static void	gen_floor_checker(t_game *g, t_tex *t, int w, int h)
{
	int	x;
	int	y;

	(void)g;
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
			put_floor_px(t, x, y);
			x++;
		}
		y++;
	}
}

int	load_floor_texture(t_game *g, const char *path)
{
	if (!load_one(g, &g->floor_tex, path))
		gen_floor_checker(g, &g->floor_tex, 64, 64);
	return (1);
}