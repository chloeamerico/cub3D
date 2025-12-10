/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:52:02 by camerico          #+#    #+#             */
/*   Updated: 2025/12/10 15:29:53 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//fonction pour extraire la map 
int	extract_map(t_game *game, int line_map_start)
{
	int	i;
	int	map_line_count;

	map_line_count = 0;
	i = line_map_start;
	while (game->file_map[i])
	{
		map_line_count++;
		i++;
	}
	game->map = malloc(sizeof(char *) * (map_line_count + 1));
	if (!game->map)
		return (1);
	i = 0;
	while (game->file_map[line_map_start])
	{
		game->map[i] = ft_strdup(game->file_map[line_map_start]);
		if (!game->map[i])
			return (free_char_tab(game->map), 1);
		i++;
		line_map_start++;
	}
	game->map[i] = NULL;
	return (0);
}

/*****************************
***********UTILS**************
*****************************/
int	check_cub_char_invalid(char *line, int nb_config)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (nb_config != 6 && line[i] != 1 && line[i] != 0 && line[i] != ' ')
			return (ft_printf("Error : invalid char or missing config\n"), 1);
		i++;
	}
	return (0);
}

int	implement_config_line(t_game *game, int *nb_config, int i)
{
	if (parse_config_line(game->file_map[i], game))
		return (1);
	(*nb_config)++;
	return (0);
}

void	err1(char **tab_couleur)
{
	free_char_tab(tab_couleur);
	ft_printf("Error : RGB color value incorrect\n");
}

void	err2(char **tab_couleur)
{
	free_char_tab(tab_couleur);
	ft_printf("Error : color should have type R,G,B\n");
}
