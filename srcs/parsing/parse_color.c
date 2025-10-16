/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:45:07 by camerico          #+#    #+#             */
/*   Updated: 2025/10/16 19:02:12 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void init_struct_couleur(t_couleur *couleur)
{
	couleur->R = NULL;
	couleur->G = NULL;
	couleur->B = NULL;
	couleur->int_r = 0;
	couleur->int_g = 0;
	couleur->int_b = 0;
}

//extrait les 3 couleurs (rgb) separees pas une virgule
//converti les str en entiers (atoi)
//on verifie que chaque couleur est dans la range & qu'il n'y a que 3 valeurs, pas de char invalides
//stocke dans la struct
int	parse_color(char *line, t_game *game, int start)
{
	t_couleur	couleur;
	
	init_struct_couleur(&couleur);
	
	
}