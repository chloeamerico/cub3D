/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:17:14 by lleichtn          #+#    #+#             */
/*   Updated: 2025/11/14 15:33:18 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <string.h>
#include <sys/time.h>

int	load_textures(t_game *g, t_pair ns, t_pair we);

static uint32_t	clr(int v)
{
	if (v < 0)
		return (0);
	if (v > 255)
		return (255);
	return (v);
}

static uint32_t	argb(int a, int r, int g, int b)
{
	uint32_t	aa;
	uint32_t	rr;
	uint32_t	gg;
	uint32_t	bb;

	aa = clr(a);
	rr = clr(r);
	gg = clr(g);
	bb = clr(b);
	return ((aa << 24) | (rr << 16) | (gg << 8) | bb);
}

static double	get_time_sec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + (tv.tv_usec / 1000000.0));
}

static void	fill_int_line(int *dst, char *src, int w)
{
	int	x;

	x = 0;
	while (x < w)
	{
		if (src[x] == '1' || src[x] == ' ')
			dst[x] = 1;
		else
			dst[x] = 0;
		x++;
	}
}

static int	**map_to_int(char **map, int w, int h)
{
	int	**out;
	int	y;

	out = malloc(sizeof(int *) * h);
	if (!out)
		return (NULL);
	y = 0;
	while (y < h)
	{
		out[y] = malloc(sizeof(int) * w);
		if (!out[y])
			return (NULL);
		fill_int_line(out[y], map[y], w);
		y++;
	}
	return (out);
}

static void	set_dir(t_game *g, char c)
{
	if (c == 'N')
	{
		g->dir_x = 0;
		g->dir_y = -1;
		g->pl_x = 0.66;
		g->pl_y = 0;
	}
	else if (c == 'S')
	{
		g->dir_x = 0;
		g->dir_y = 1;
		g->pl_x = -0.66;
		g->pl_y = 0;
	}
	else if (c == 'E')
	{
		g->dir_x = 1;
		g->dir_y = 0;
		g->pl_x = 0;
		g->pl_y = 0.66;
	}
	else if (c == 'W')
	{
		g->dir_x = -1;
		g->dir_y = 0;
		g->pl_x = 0;
		g->pl_y = -0.66;
	}
}

static void	find_player(t_game *g)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < g->map_h)
	{
		x = 0;
		while (x < g->map_w)
		{
			c = g->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				g->px = x + 0.5;
				g->py = y + 0.5;
				return (set_dir(g, c));
			}
			x++;
		}
		y++;
	}
	g->px = 2.5;
	g->py = 2.5;
	g->dir_x = -1;
	g->dir_y = 0;
	g->pl_x = 0;
	g->pl_y = -0.66;
}

static void	free_all_local(t_game *g)
{
	if (!g)
		return ;
	free_char_tab(g->file_map);
	free_char_tab(g->map);
	if (g->map_int)
		free_int_tab(g->map_int, g->map_h);
	if (g->config)
		free(g->config);
	if (g->data)
		free(g->data);
}

static int	loop_hook(t_game *g)
{
	static double	t0 = 0;
	double			t1;
	double			dt;

	t1 = get_time_sec();
	if (t0 == 0)
		t0 = t1;
	dt = t1 - t0;
	t0 = t1;
	player_update(g, dt);
	render_frame(g);
	return (0);
}

static int	do_parse(t_game *g, int ac, char **av)
{
	if (check_arg(ac, av))
		return (1);
	if (init_struct(g, av))
		return (1);
	if (divide_map_config(g))
		return (1);
	if (parsing_map(g))
		return (1);
	return (0);
}

static int	load_all_textures(t_game *g)
{
	t_pair	ns;
	t_pair	we;

	ns.a = g->config->no_texture;
	ns.b = g->config->so_texture;
	we.a = g->config->we_texture;
	we.b = g->config->ea_texture;
	if (!load_textures(g, ns, we))
		return (0);
	load_floor_texture(g, "texture/grass.xpm");
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_game	g;

	(void)envp;
	memset(&g, 0, sizeof(g));
	g.mouse_sens = 0.0025;
	if (do_parse(&g, ac, av))
		return (free_all_local(&g), 1);
	g.map_w = g.data->map_width;
	g.map_h = g.data->map_height;
	g.map_int = map_to_int(g.map, g.map_w, g.map_h);
	if (!g.map_int)
		return (free_all_local(&g), 1);
	find_player(&g);
	g.ceil_col = argb(255, 135, 206, 235);
	g.floor_col = argb(255, 68, 68, 68);
	if (!init_mlx(&g) || !frame_new(&g, W, H))
		return (free_all_local(&g), 1);
	if (!load_all_textures(&g))
		return (free_all_local(&g), 1);
	free_char_tab(g.file_map);
	memset(g.key, 0, sizeof(g.key));
	mlx_hook(g.win, 17, 0, close_win, &g);
	mlx_hook(g.win, 2, 1L << 0, key_press, &g);
	mlx_hook(g.win, 3, 1L << 1, key_release, &g);
	mlx_hook(g.win, 4, 1L << 2, mouse_press, &g);
	mlx_hook(g.win, 5, 1L << 3, mouse_release, &g);
	mlx_hook(g.win, 6, 1L << 6, mouse_move, &g);
	mlx_loop_hook(g.mlx, loop_hook, &g);
	mlx_loop(g.mlx);
	free_all_local(&g);
	return (0);
}
