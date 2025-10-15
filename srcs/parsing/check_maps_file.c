/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_maps_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:24:56 by camerico          #+#    #+#             */
/*   Updated: 2025/10/15 17:00:47 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//verifie si c''est une ligne vide, ou avec que des espaces ou tab ou \n
//return (1) si line vide, return (0) si il y a qqch
int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if(!line)
		return(1);
	while(line[i])
	{
		if(line[i] != ' ' || line[i] != '\t' || line[i] != "\n")
			return(0);
		i++;
	}
	return(1);
}

//verifie si c'est une ligne de config ou la map a extraire
//lignes de config commencent par : NO, SO, WE, EA, F, ou C
//return (0) si c'est une ligne de config
int	is_config_line(char *line)
{
	int	i;

	i = 0;
	if(!line)
		return (1);
	while (line[i] == ' ' || line[i] == '\t')			//pour skip les expaces et tab au deb
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return(0);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return(0);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		return(0);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		return(0);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		return(0);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		return(0);
	return (1);
}

//on verifie si c'est bien le debut de la carte
//return (1) si c'est le debut de la map
int	is_map_start(char *line)
{
	int	i;

	i = 0;
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	if(line[i] == '1' || line[i] == '0' || line[i] == 'N' ||
		line[i] == 'S' || line[i] == 'E' || line[i] == 'W');
		return(1);
	return(0);
}

//fonction qui va diviser le fichier map en 2, d'un cote la config 
int divide_map_config(t_game *game)
{
	int	i;
	int	nb_config;		//va compter le nb de config, il en faut 6 au total

	i = 0;
	nb_config = 0;
	while(game->file_map[i])
	{
		if (is_empty_line(game->file_map[i]))
		{
			i++;
			continue;		//on recommence la boucle while sans passer les autres boucles
		}
		if(is_config_line(game->file_map[i]) == 0)		//si c'est une ligne de config
		{
			
		}
	}
	
}