/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:32:53 by camerico          #+#    #+#             */
/*   Updated: 2025/12/02 14:40:30 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	mlx_mouse_hide(void *mlx, void *win);
int	mlx_mouse_show(void *mlx, void *win);
int	mlx_mouse_move(void *mlx, void *win, int x, int y);

void	center_mouse(t_game *g)
{
	mlx_mouse_move(g->mlx, g->win, W / 2, H / 2);
}

int	mouse_press(int button, int x, int y, t_game *g)
{
	(void)x;
	(void)y;
	if (button == 1 && !g->mouse_captured)
	{
		g->mouse_captured = 1;
		mlx_mouse_hide(g->mlx, g->win);
		center_mouse(g);
	}
	return (0);
}

int	mouse_move(int x, int y, t_game *g)
{
	int		dx;
	double	a;

	(void)y;
	if (!g->mouse_captured)
		return (0);
	dx = x - (W / 2);
	if (dx != 0)
	{
		a = (double)dx * g->mouse_sens;
		rotate_player(g, a);
		center_mouse(g);
	}
	return (0);
}

void	rotate_player(t_game *g, double a)
{
	double	ox;
	double	px;

	ox = g->dir_x;
	px = g->pl_x;
	g->dir_x = g->dir_x * cos(a) - g->dir_y * sin(a);
	g->dir_y = ox * sin(a) + g->dir_y * cos(a);
	g->pl_x = g->pl_x * cos(a) - g->pl_y * sin(a);
	g->pl_y = px * sin(a) + g->pl_y * cos(a);
}

void	player_rotate_keys(t_game *g, double dt)
{
	double	speed;

	speed = 2.5 * dt;
	if (g->key[XK_Left])
		rotate_player(g, -speed);
	if (g->key[XK_Right])
		rotate_player(g, speed);
}
