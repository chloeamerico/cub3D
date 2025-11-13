/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:52:02 by camerico          #+#    #+#             */
/*   Updated: 2025/10/22 15:12:49 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//fonction pour extraire la map 

int extract_map(t_game *game, int line_map_start)
{
	int		i;

	i = 0;
	game->map = malloc(sizeof(char *) * 100);
	if (!game->map)
		return (1);
	while(game->file_map[line_map_start])
	{
		game->map[i] = ft_strdup(game->file_map[line_map_start]);
		i++;
		line_map_start++;
	}
	game->map[i] = NULL;
	// i = 0;								//pour afficher la map
	// while(game->map[i])
	// {
	// 	ft_printf("%s", game->map[i]);
	// 	i++;
	// }
	return (0);
}