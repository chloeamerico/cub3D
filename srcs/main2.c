/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:43:41 by camerico          #+#    #+#             */
/*   Updated: 2025/12/04 16:00:55 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_and_parse(t_game *g, int ac, char **av)
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

int	setup_world(t_game *g)
{
	g->map_w = g->data->map_width;
	g->map_h = g->data->map_height;
	g->map_int = map_char_to_int(g->map, g->map_w, g->map_h);
	if (!g->map_int)
		return (1);
	find_player(g);
	g->ceil_color = (g->config.c[0] << 16)
	              | (g->config.c[1] << 8)
	              | g->config.c[2];
	
	g->floor_color = (g->config.f[0] << 16)
	               | (g->config.f[1] << 8)
	               | g->config.f[2];
		return (0);
}

uint32_t	clr(int v)
{
	if (v < 0)
		return (0);
	if (v > 255)
		return (255);
	return (v);
}
