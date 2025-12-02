/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:29:25 by camerico          #+#    #+#             */
/*   Updated: 2025/12/02 14:36:05 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int key, t_game *g)
{
	if (key >= 0 && key < 65536)
		g->key[key] = 1;
	if (key == XK_Escape)
		close_win(g);
	return (0);
}

int	key_release(int key, t_game *g)
{
	if (key >= 0 && key < 65536)
		g->key[key] = 0;
	return (0);
}

int	close_win(t_game *g)
{
	free_all_local(g);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	mlx_destroy_display(g->mlx);
	free(g->mlx);
	exit(0);
}
