/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:45:14 by camerico          #+#    #+#             */
/*   Updated: 2025/12/02 15:45:17 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_char_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free (tab[i]);
		i++;
	}
	free (tab);
}

void	free_int_tab(int **tab, int h)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (i < h)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// void	free_mlx(t_game *g)
// {
// 	if (g->win)
// 		mlx_destroy_window(g->mlx, g->win);
// 	if (g->tex_no.i.img)
// 		mlx_destroy_image(g->mlx, g->tex_no.i.img);
// 	if (g->tex_so.i.img)
// 		mlx_destroy_image(g->mlx, g->tex_so.i.img);
// 	if (g->tex_we.i.img)
// 		mlx_destroy_image(g->mlx, g->tex_we.i.img);
// 	if (g->tex_ea.i.img)
// 		mlx_destroy_image(g->mlx, g->tex_ea.i.img);
// 	if (g->floor_tex.i.img)
// 		mlx_destroy_image(g->mlx, g->floor_tex.i.img);
// 	if (g->frame.img)
// 		mlx_destroy_image(g->mlx, g->frame.img);
// 	mlx_destroy_display(g->mlx);
// 	free(g->mlx);
// }


static void	free_texture(t_game *game)
{
	if (game->config.ea_texture)
		free(game->config.ea_texture);
	if (game->config.so_texture)
		free(game->config.so_texture);
	if (game->config.no_texture)
		free(game->config.no_texture);
	if (game->config.we_texture)
		free(game->config.we_texture);
}

void	free_all_local(t_game *g)
{
	if (!g)
		return ;
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
	if (g->frame.img)
		mlx_destroy_image(g->mlx, g->frame.img);
	free_char_tab(g->file_map);
	free_char_tab(g->map);
	if (g->map_int)
		free_int_tab(g->map_int, g->map_h);
	if (g->data)
		free(g->data);
	free_texture(g);	
}
