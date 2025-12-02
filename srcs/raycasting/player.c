/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 11:41:33 by lleichtn          #+#    #+#             */
/*   Updated: 2025/12/02 14:41:30 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <math.h>

static int	blocked(t_game *g, double nx, double ny)
{
	int	mx;
	int	my;

	mx = (int)nx;
	my = (int)ny;
	if (mx < 0 || my < 0)
		return (1);
	if (mx >= g->map_w || my >= g->map_h)
		return (1);
	if (g->map_int[my][mx] == 1)
		return (1);
	return (0);
}

static void	player_move_fb(t_game *g, double sp)
{
	double	nx;
	double	ny;

	if (g->key[XK_w] || g->key[XK_z])
	{
		nx = g->px + g->dir_x * sp;
		ny = g->py + g->dir_y * sp;
		if (!blocked(g, nx, g->py))
			g->px = nx;
		if (!blocked(g, g->px, ny))
			g->py = ny;
	}
	if (g->key[XK_s])
	{
		nx = g->px - g->dir_x * sp;
		ny = g->py - g->dir_y * sp;
		if (!blocked(g, nx, g->py))
			g->px = nx;
		if (!blocked(g, g->px, ny))
			g->py = ny;
	}
}

static void	player_move_strafe(t_game *g, double sp)
{
	double	nx;
	double	ny;

	if (g->key[XK_a] || g->key[XK_q])
	{
		nx = g->px + g->dir_y * sp;
		ny = g->py - g->dir_x * sp;
		if (!blocked(g, nx, g->py))
			g->px = nx;
		if (!blocked(g, g->px, ny))
			g->py = ny;
	}
	if (g->key[XK_d])
	{
		nx = g->px - g->dir_y * sp;
		ny = g->py + g->dir_x * sp;
		if (!blocked(g, nx, g->py))
			g->px = nx;
		if (!blocked(g, g->px, ny))
			g->py = ny;
	}
}

// void	rotate_player(t_game *g, double a)
// {
// 	double	ox;
// 	double	px;

// 	ox = g->dir_x;
// 	px = g->pl_x;
// 	g->dir_x = g->dir_x * cos(a) - g->dir_y * sin(a);
// 	g->dir_y = ox * sin(a) + g->dir_y * cos(a);
// 	g->pl_x = g->pl_x * cos(a) - g->pl_y * sin(a);
// 	g->pl_y = px * sin(a) + g->pl_y * cos(a);
// }

void	player_update(t_game *g, double dt)
{
	double	sp;

	sp = 3.0 * dt;
	player_move_fb(g, sp);
	player_move_strafe(g, sp);
	player_rotate_keys(g, dt);
}

// int	key_press(int key, t_game *g)
// {
// 	if (key >= 0 && key < 65536)
// 		g->key[key] = 1;
// 	if (key == XK_Escape)
// 		close_win(g);
// 	return (0);
// }

// int	key_release(int key, t_game *g)
// {
// 	if (key >= 0 && key < 65536)
// 		g->key[key] = 0;
// 	return (0);
// }

// int	close_win(t_game *g)
// {
// 	free_all_local(g);
// 	if (g->win)
// 		mlx_destroy_window(g->mlx, g->win);
// 	mlx_destroy_display(g->mlx);
// 	free(g->mlx);
// 	exit(0);
// }

// void	center_mouse(t_game *g)
// {
// 	mlx_mouse_move(g->mlx, g->win, W / 2, H / 2);
// }

// int	mouse_press(int button, int x, int y, t_game *g)
// {
// 	(void)x;
// 	(void)y;
// 	if (button == 1 && !g->mouse_captured)
// 	{
// 		g->mouse_captured = 1;
// 		mlx_mouse_hide(g->mlx, g->win);
// 		center_mouse(g);
// 	}
// 	return (0);
// }

int	mouse_release(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (button == 3 && g->mouse_captured)
	{
		g->mouse_captured = 0;
		mlx_mouse_show(g->mlx, g->win);
	}
	return (0);
}
