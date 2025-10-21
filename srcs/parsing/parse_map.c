/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:22:41 by camerico          #+#    #+#             */
/*   Updated: 2025/10/21 17:10:46 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//verifie que la map ne contient que des char autorises : 0, 1, (espace), et N/S/E/W
static int	check_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	while(map[i])
	{
		if(is_empty_line(map[i]))
			return(ft_printf("Error : empty line in map\n"), 1);
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '0' && map[i][j] != '1' && map[i][j] != ' '
				&& map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'E'
				&& map[i][j] != 'W' && map[i][j] != '\n')
				return (ft_printf("Error : invalid char %c in map\n", map[i][j]), 1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	init_data_struct(t_game *game)
{
	game->data = malloc(sizeof(t_data));
	if(!game->data)
		return(1);
	game->data->map_height = 0;
	game->data->map_width = 0;
	game->data->player_dir = 0;
	game->data->player_x = 0;
	game->data->player_y = 0;
	return (0);
}

//verifie qu'il n'y a qu'un seul player sur la map, on rejete si il y en a pas ou plus que 1
//stocke la position x, y du joueur et son orientation
static int	check_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while(game->map[i])
	{
		j = 0;
		while(game->map[i][j])
		{
			if(game->map[i][j] == 'N' || game->map[i][j] == 'S' || game->map[i][j] == 'E'
				|| game->map[i][j] == 'W')
			{
				if(game->data->player_dir != 0)
					return(ft_printf("Error : More than one player detected\n"), 1);
				game->data->player_dir = game->map[i][j];
				game->data->player_x = j;
				game->data->player_y = i;
			}
			j++;
		}
		i++;
	}
	if(game->data->player_dir == 0)
		return(ft_printf("Error : Any player detected on the map\n"), 1);
	return (0);
}

int	parsing_map(t_game *game)
{
	// int	i = 0;							//pour afficher la map
	
	// while(game->map[i])
	// {
	// 	ft_printf("%s", game->map[i]);
	// 	i++;
	// }
	if (check_char(game->map))
		return (1);
	if(init_data_struct(game))
		return(1);
	if(check_player(game))
		return(1);
	return (0);
}

