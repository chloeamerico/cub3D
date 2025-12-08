/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_text2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 18:47:27 by lleichtn          #+#    #+#             */
/*   Updated: 2025/12/08 16:40:22 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	set_no(t_game *g, char *path)
{
	if (g->config.no_texture)
	{
		free(path);
		free(g->config.no_texture);
		g->config.no_texture = NULL;
		return (ft_printf("Error : double North texture detected\n"), 1);
	}
	g->config.no_texture = path;
	return (0);
}

static int	set_so(t_game *g, char *path)
{
	if (g->config.so_texture)
	{
		free(path);
		free(g->config.so_texture);
		g->config.so_texture = NULL;
		return (ft_printf("Error : double South texture detected\n"), 1);
	}
	g->config.so_texture = path;
	return (0);
}

static int	set_we(t_game *g, char *path)
{
	if (g->config.we_texture)
	{
		free(path);
		free(g->config.we_texture);
		g->config.we_texture = NULL;
		return (ft_printf("Error : double West texture detected\n"), 1);
	}
	g->config.we_texture = path;
	return (0);
}

static int	set_ea(t_game *g, char *path)
{
	if (g->config.ea_texture)
	{
		free(path);
		free(g->config.ea_texture);
		g->config.ea_texture = NULL;
		return (ft_printf("Error : double East texture detected\n"), 1);
	}
	g->config.ea_texture = path;
	return (0);
}

int	add_struct(t_game *g, char *path, char *line, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && (line[i + 2] == ' ' 
		|| line[i + 2] == '\t'))
		return (set_no(g, path));
	if (line[i] == 'S' && line[i + 1] == 'O' && (line[i + 2] == ' '
		|| line[i + 2] == '\t'))
		return (set_so(g, path));
	if (line[i] == 'W' && line[i + 1] == 'E' && (line[i + 2] == ' '
		|| line[i + 2] == '\t'))
		return (set_we(g, path));
	if (line[i] == 'E' && line[i + 1] == 'A' && (line[i + 2] == ' '
		|| line[i + 2] == '\t'))
		return (set_ea(g, path));
	free(path);
	return (ft_printf("Error : invalid texture identifier\n"), 1);
}
