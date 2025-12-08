/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_maps_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:24:56 by camerico          #+#    #+#             */
/*   Updated: 2025/12/08 16:42:09 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//verifie si c''est une ligne vide, ou avec que des espaces ou tab ou \n
//return (1) si line vide, return (0) si il y a qqch
int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

//verifie si c'est une ligne de config ou la map a extraire
//lignes de config commencent par : NO, SO, WE, EA, F, ou C
//return (0) si c'est une ligne de config
int	is_config_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && (line[i + 2] == ' ' 
		|| line[i + 2] == '\t'))
		return (0);
	else if (line[i] == 'S' && line[i + 1] == 'O' && (line[i + 2] == ' '
		|| line[i + 2] == '\t'))
		return (0);
	else if (line[i] == 'W' && line[i + 1] == 'E' && (line[i + 2] == ' '
		|| line[i + 2] == '\t'))
		return (0);
	else if (line[i] == 'E' && line[i + 1] == 'A' && (line[i + 2] == ' '
		|| line[i + 2] == '\t'))
		return (0);
	else if (line[i] == 'F' && (line[i + 1] == ' ' || line[i + 2] == '\t'))
		return (0);
	else if (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 2] == '\t'))
		return (0);
	return (1);
}

static int	find_map_start(t_game *game, int *nb_config)
{
	int	i;

	i = 0;
	while (game->file_map[i])
	{
		if (is_empty_line(game->file_map[i]))
		{
			i++;
			continue ;
		}
		if (is_config_line(game->file_map[i]) == 0)
		{
			if (implement_config_line(game, nb_config, i))
				return (-2);
		}
		else if (check_cub_char_invalid(game->file_map[i], *nb_config))
			return (-2);
		else
			return (i);
		i++;
	}
	return (-1);
}

//fonction qui va diviser le fichier map en 2, d'un cote la config 
int	divide_map_config(t_game *game)
{
	int	nb_config;
	int	line_map_start;

	nb_config = 0;
	line_map_start = find_map_start(game, &nb_config);
	if (nb_config != 6 && line_map_start == -1)
		return (ft_printf("Error : missing config\n"), 1);
	if (line_map_start == -2)
		return (1);
	if (line_map_start == -1)
		return (ft_printf("Error : map not found\n"), 1);
	return (extract_map(game, line_map_start));
}

// AVANT DE REDUIRE
//fonction qui va diviser le fichier map en 2, d'un cote la config 
// int	divide_map_config(t_game *game)
// {
// 	int	i;
// 	int	nb_config;
// 	int	line_map_start;

// 	i = 0;
// 	nb_config = 0;
// 	line_map_start = -1;
// 	while (game->file_map[i])
// 	{
// 		if (is_empty_line(game->file_map[i]))
// 		{
// 			i++;
// 			continue ;
// 		}
// 		if (is_config_line(game->file_map[i]) == 0)
// 		{
// 			if (parse_config_line(game->file_map[i], game))
// 				return (1);
// 			nb_config++;
// 		}
// 		else if (check_cub_char_invalid(game->file_map[i], nb_config))
// 			return (1);
// 		else
// 		{
// 			line_map_start = i;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (nb_config != 6)
// 		return (ft_printf("Error : missing config\n"), 1);
// 	if (line_map_start == -1)
// 		return (ft_printf("Error : map not found\n"));
// 	return (extract_map(game, line_map_start));
// }

//fonction qui recoit une ligne identifiee precedemment comme une line de config
//identifie si c'est NO, SO... 
//et remplie la structure avec le chemin pour y acceder ou couleur RGB
//valide les donnees
int	parse_config_line(char *line, t_game *game)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
	{
		i += 2;
		if (parse_texture(line, i, game))
			return (1);
	}
	else if (line[i] == 'F' || line[i] == 'C')
	{
		i++;
		if (parse_color(line, game, i))
			return (1);
	}
	return (0);
}
