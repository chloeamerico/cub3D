/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:16:14 by lleichtn          #+#    #+#             */
/*   Updated: 2025/12/02 18:22:37 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <string.h>
#include <sys/time.h>

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
	int	len;

	len = ft_strlen(src);
	x = 0;
	while (x < w)
	{
		if (x >= len || src[x] == ' ' || src[x] == '\n')
			dst[x] = 1;
		else if (src[x] == '1')
			dst[x] = 1;
		else
			dst[x] = 0;
		x++;
	}
}


static int	**map_char_to_int(char **map, int w, int h)
{
	int	**m;
	int	y;

	m = malloc(sizeof(int *) * h);
	if (!m)
		return (NULL);
	y = 0;
	while (y < h)
	{
		m[y] = malloc(sizeof(int) * w);
		if (!m[y])
			return (NULL);
		fill_int_line(m[y], map[y], w);
		y++;
	}
	return (m);
}

// static void	set_dir(t_game *g, char c)
// {
// 	if (c == 'N')
// 	{
// 		g->dir_x = 0;
// 		g->dir_y = -1;
// 		g->pl_x = 0.66;
// 		g->pl_y = 0;
// 	}
// 	else if (c == 'S')
// 	{
// 		g->dir_x = 0;
// 		g->dir_y = 1;
// 		g->pl_x = -0.66;
// 		g->pl_y = 0;
// 	}
// 	else if (c == 'E')
// 	{
// 		g->dir_x = 1;
// 		g->dir_y = 0;
// 		g->pl_x = 0;
// 		g->pl_y = 0.66;
// 	}
// 	else if (c == 'W')
// 	{
// 		g->dir_x = -1;
// 		g->dir_y = 0;
// 		g->pl_x = 0;
// 		g->pl_y = -0.66;
// 	}
// }

static void	set_dir_ns(t_game *g, char c)
{
	if (c == 'N')
	{
		g->dir_x = 0;
		g->dir_y = -1;
		g->pl_x = 0.66;
		g->pl_y = 0;
	}
	else
	{
		g->dir_x = 0;
		g->dir_y = 1;
		g->pl_x = -0.66;
		g->pl_y = 0;
	}
}

static void	set_dir_ew(t_game *g, char c)
{
	if (c == 'E')
	{
		g->dir_x = 1;
		g->dir_y = 0;
		g->pl_x = 0;
		g->pl_y = 0.66;
	}
	else
	{
		g->dir_x = -1;
		g->dir_y = 0;
		g->pl_x = 0;
		g->pl_y = -0.66;
	}
}

static void	set_dir(t_game *g, char c)
{
	if (c == 'N' || c == 'S')
		set_dir_ns(g, c);
	else
		set_dir_ew(g, c);
}

// static void	find_player(t_game *g)
// {
// 	int		x;
// 	int		y;
// 	char	c;

// 	y = 0;
// 	while (y < g->map_h)
// 	{
// 		x = 0;
// 		while (x < g->map_w)
// 		{
// 			c = g->map[y][x];
// 			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
// 			{
// 				g->px = x + 0.5;
// 				g->py = y + 0.5;
// 				set_dir(g, c);
// 				return ;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// 	g->px = 2.5;
// 	g->py = 2.5;
// 	g->dir_x = -1;
// 	g->dir_y = 0;
// 	g->pl_x = 0;
// 	g->pl_y = -0.66;
// }

static int	find_player_in_line(t_game *g, int y)
{
	int		x;
	char	c;
	int		len;

	len =ft_strlen(g->map[y]);
	x = 0;
	while (x < len)
	{
		c = g->map[y][x];
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			g->px = x + 0.5;
			g->py = y + 0.5;
			set_dir(g, c);
			return (1);
		}
		x++;
	}
	return (0);
}

static void	find_player(t_game *g)
{
	int	y;

	y = 0;
	while (y < g->map_h)
	{
		if (find_player_in_line(g, y))
			return ;
		y++;
	}
	g->px = 2.5;
	g->py = 2.5;
	g->dir_x = -1;
	g->dir_y = 0;
	g->pl_x = 0;
	g->pl_y = -0.66;
}

// void	free_all_local(t_game *g)
// {
// 	if (!g)
// 		return ;
// 	free_char_tab(g->file_map);
// 	free_char_tab(g->map);
// 	if (g->map_int)
// 		free_int_tab(g->map_int, g->map_h);
// 	if (g->config)
// 		free(g->config);
// 	if (g->data)
// 		free(g->data);
// }

// void	free_all_local(t_game *g)
// {
// 	int	i;

// 	if (!g)
// 		return ;

// 	i = 0;
// 	while (i < TEX_NB)
// 	{
// 		if (g->tex[i].i.img)
// 			mlx_destroy_image(g->mlx, g->tex[i].i.img);
// 		i++;
// 	}

// 	if (g->frame.img)
// 		mlx_destroy_image(g->mlx, g->frame.img);

// 	free_char_tab(g->file_map);
// 	free_char_tab(g->map);

// 	if (g->map_int)
// 		free_int_tab(g->map_int, g->map_h);

// 	if (g->config)
// 		free(g->config);

// 	if (g->data)
// 		free(g->data);
// }




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

// static int	do_parse(t_game *g, int ac, char **av)
// {
// 	if (check_arg(ac, av))
// 		return (1);
// 	if (init_struct(g, av))
// 		return (1);
// 	if (divide_map_config(g))
// 		return (1);
// 	if (parsing_map(g))
// 		return (1);
// 	return (0);
// }

// static int	load_all_textures(t_game *g)
// {
// 	t_pair	ns;
// 	t_pair	we;

// 	ns.a = "texture/nord.xpm";
// 	ns.b = "texture/sud.xpm";
// 	we.a = "texture/ouest.xpm";
// 	we.b = "texture/est.xpm";
// 	if (!load_textures(g, ns, we))
// 		return (0);
// 	load_floor_texture(g, "texture/grass.xpm");
// 	return (1);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	t_game	g;

// 	(void)envp;
// 	memset(&g, 0, sizeof(g));
// 	g.mouse_sens = 0.0025;
// 	if (do_parse(&g, ac, av))
// 		return (free_all_local(&g), 1);
// 	g.map_w = g.data->map_width;
// 	g.map_h = g.data->map_height;
// 	g.map_int = map_char_to_int(g.map, g.map_w, g.map_h);
// 	if (!g.map_int)
// 		return (free_all_local(&g), 1);
// 	find_player(&g);
// 	g.ceil_col = argb(255, 0x87, 0xCE, 0xEB);
// 	g.floor_col = argb(255, 0x44, 0x44, 0x44);
// 	if (!init_mlx(&g) || !frame_new(&g, W, H))
// 		return (free_all_local(&g), 1);
// 	if (!load_all_textures(&g))
// 		return (free_all_local(&g), 1);
// 	free_char_tab(g.file_map);
// 	memset(g.key, 0, sizeof(g.key));
// 	mlx_hook(g.win, 17, 0, close_win, &g);
// 	mlx_hook(g.win, 2, 1L << 0, key_press, &g);
// 	mlx_hook(g.win, 3, 1L << 1, key_release, &g);
// 	mlx_hook(g.win, 4, 1L << 2, mouse_press, &g);
// 	mlx_hook(g.win, 5, 1L << 3, mouse_release, &g);
// 	mlx_hook(g.win, 6, 1L << 6, mouse_move, &g);
// 	mlx_loop_hook(g.mlx, loop_hook, &g);
// 	mlx_loop(g.mlx);
// 	free_all_local(&g);
// 	return (0);
// }

static int	init_and_parse(t_game *g, int ac, char **av)
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

static int	setup_world(t_game *g)
{
	g->map_w = g->data->map_width;
	g->map_h = g->data->map_height;
	g->map_int = map_char_to_int(g->map, g->map_w, g->map_h);
	if (!g->map_int)
		return (1);
	find_player(g);
	g->ceil_col = argb(255, 0x87, 0xCE, 0xEB);
	g->floor_col = argb(255, 0x44, 0x44, 0x44);
	return (0);
}

static void	start_loop(t_game *g)
{
	memset(g->key, 0, sizeof(g->key));
	mlx_hook(g->win, 17, 0, close_win, g);
	mlx_hook(g->win, 2, 1L << 0, key_press, g);
	mlx_hook(g->win, 3, 1L << 1, key_release, g);
	mlx_hook(g->win, 4, 1L << 2, mouse_press, g);
	mlx_hook(g->win, 5, 1L << 3, mouse_release, g);
	mlx_hook(g->win, 6, 1L << 6, mouse_move, g);
	mlx_loop_hook(g->mlx, loop_hook, g);
	mlx_loop(g->mlx);
}

int	main(int ac, char **av, char **envp)
{
	t_game	g;

	(void)envp;
	memset(&g, 0, sizeof(g));
	g.mouse_sens = 0.0025;

	if (init_and_parse(&g, ac, av))
		return (free_all_local(&g), 1);

	if (setup_world(&g))
		return (free_all_local(&g), 1);

	// // DEBUG : afficher les chemins
	// printf("NO = %s\n", g.config.no_texture);
	// printf("SO = %s\n", g.config.so_texture);
	// printf("WE = %s\n", g.config.we_texture);
	// printf("EA = %s\n", g.config.ea_texture);

	if (!init_mlx(&g) || !frame_new(&g, W, H))
		return (free_all_local(&g), 1);

	if (!load_wall_textures(&g))
		return (free_all_local(&g), 1);

	load_floor_texture(&g, "texture/grass.xpm");

	start_loop(&g);
	free_all_local(&g);
	return (0);
}

