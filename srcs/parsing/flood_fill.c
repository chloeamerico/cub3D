/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 12:56:08 by camerico          #+#    #+#             */
/*   Updated: 2025/11/06 12:00:41 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*   
	Vérification locale : Chaque cellule traversable est-elle entourée de murs ou d'autres cellules traversables ?
    Vérification globale : Toute la zone traversable est-elle connectée en un seul bloc ?

*/

//verifie que la map est bien close avec des 1 au debut et a la fin de chaque ligne
// int	check_map_close(t_game *game, char **map)
// {
	
// }


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
static int	flood_fill(char **map, int x, int y, t_game *game)
{
	 if (y < 0 || y >= game->data->map_height)		//on check si on est dans les lim de la map
        return (1);
	 if (x < 0 || x >= (int)ft_strlen(map[y]))		//on check si on est dans les lim de cette ligne
        return (1);
	// ft_printf("on check le char %c en ligne %i et colonne %i\n", map[y][x], y, x);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (0);
	if(map[y][x] == '\n' || map[y][x] == '\0')		//si c'est un espace, on check si il est sur un bord
		return (1);
	if (map[y][x] != '0' && map[y][x] != 'N' && map[y][x] != 'S' 
        && map[y][x] != 'E' && map[y][x] != 'W')
        return (1);
	map[y][x] = 'V';
	if(flood_fill(map, x - 1, y, game) == 1)
		return (1);
	if (flood_fill(map, x + 1, y, game) == 1)
		return (1);
	if(flood_fill(map, x, y - 1, game) == 1)
		return(1);
	if (flood_fill(map, x, y + 1, game) == 1)
		return (1);
	return (0);
}


// // //fonction pour explorer la map
// static int	flood_fill(char **map, int x, int y, t_game *game)
// {
// 	 if (y < 0 || y >= game->data->map_height)		//on check si on est dans les lim de la map
//         return (1);
// 	 if (x < 0 || x >= (int)ft_strlen(map[y]))		//on check si on est dans les lim de cette ligne
//         return (1);
// 	ft_printf("on check le char %c en ligne %i et colonne %i\n", map[y][x], y, x);
// 	if (map[y][x] == '1' || map[y][x] == 'V')
// 		return (0);
// 	if(map[y][x] == ' ' || map[y][x] == '\n' || map[y][x] == '\0')		//si c'est un espace, on check si il est sur un bord
// 	{
// 		if(y == 0 || y == game->data->map_height - 1
// 			|| x == 0 || x == (int)ft_strlen(map[y]) - 1)
// 			return (1);
// 		return (0);
// 	}
// 	if (map[y][x] != '0' && map[y][x] != 'N' && map[y][x] != 'S' 
//         && map[y][x] != 'E' && map[y][x] != 'W')
//         return (0);
// 	map[y][x] = 'V';
// 	if(flood_fill(map, x - 1, y, game) == 1)
// 		return (1);
// 	if (flood_fill(map, x + 1, y, game) == 1)
// 		return (1);
// 	if(flood_fill(map, x, y - 1, game) == 1)
// 		return(1);
// 	if (flood_fill(map, x, y + 1, game) == 1)
// 		return (1);
// 	return (0);
// }

// //une fois qu'on a valide que la map etait valide, on remplace les espaces par des 0 sur la map de base
// static void	replace_space(t_game *game)
// {
// 	int i;
// 	int j;
// 	i = 0;
// 	while (i < game->data->map_height)
// 	{
// 		j = 0;
// 		while (game->map[i][j])
// 		{
// 			if (game->map[i][j] == ' ')
// 		    	game->map[i][j] = '0';
// 			j++;
// 		}
// 		i++;
// 	}
// }

//la fonction qui verifie si le chemin est valide
int	valid_path(t_game *game)
{
	char	**copy;
	int		result;
	// int		i;
	
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
	// replace_space(game);
	// i = 0;								//pour afficher la map
	// while(copy[i])
	// {
	// 	ft_printf("%s", copy[i]);
	// 	i++;
	// }
	// free_tab(copy);
	return (0);
}
