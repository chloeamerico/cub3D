/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:46:25 by camerico          #+#    #+#             */
/*   Updated: 2025/12/03 13:05:28 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static void	set_dir(t_game *g, char c)
{
	if (c == 'N' || c == 'S')
		set_dir_ns(g, c);
	else
		set_dir_ew(g, c);
}

static int	find_player_in_line(t_game *g, int y)
{
	int		x;
	char	c;
	int		len;

	len = ft_strlen(g->map[y]);
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

void	find_player(t_game *g)
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
