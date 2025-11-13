/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:56:08 by camerico          #+#    #+#             */
/*   Updated: 2025/11/13 17:24:08 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//creer une copie de la cap pour ne pas affecter l'initiale
static char	**copy_map(t_game *game)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof (char *) * (game->data->map_height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < game->data->map_height)
	{
		copy[i] = ft_strdup(game->map[i]);
		if (!copy[i])
		{
			while (i > 0)
				free(copy[--i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// //fonction pour explorer la map
//on check si on est dans les lim de la map
//puis on check si on est dans les lim de cette ligne
//si c'est un espace, on check si il est sur un bord
static int	flood_fill(char **map, int x, int y, t_game *game)
{
	if (y < 0 || y >= game->data->map_height)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(map[y]))
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if (map[y][x] == '\n' || map[y][x] == '\0')
		return (1);
	if (map[y][x] != '0' && map[y][x] != 'N' && map[y][x] != 'S'
		&& map[y][x] != 'E' && map[y][x] != 'W')
		return (1);
	map[y][x] = 'V';
	if (flood_fill(map, x - 1, y, game) == 1)
		return (1);
	if (flood_fill(map, x + 1, y, game) == 1)
		return (1);
	if (flood_fill(map, x, y - 1, game) == 1)
		return (1);
	if (flood_fill(map, x, y + 1, game) == 1)
		return (1);
	return (0);
}

//la fonction qui verifie si le chemin est valide
int	valid_path(t_game *game)
{
	char	**copy;
	int		result;

	copy = NULL;
	copy = copy_map(game);
	if (!copy)
		return (ft_printf("Error: failed to copy map\n"), 1);
	result = flood_fill(copy, game->data->player_x, game->data->player_y, game);
	free_char_tab(copy);
	if (result == 1)
	{
		ft_printf("Error : Map not closed\n");
		return (1);
	}
	return (0);
}
