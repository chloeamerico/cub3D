/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:45:07 by camerico          #+#    #+#             */
/*   Updated: 2025/10/17 19:22:05 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void init_struct_couleur(t_couleur *couleur)
{
	couleur->R = 0;
	couleur->G = 0;
	couleur->B = 0;
}

//fait un split pour extraire les valeurs dans un tab
// on verifie qu'il n'y ait que 3 valeurs
static char	**extract_color(char *line, int i)
{
	char **tab_couleur;
	int j;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	tab_couleur = ft_split(line + i, ',');
	if(!tab_couleur)
		return(NULL);
	i = 0;
	while (tab_couleur[i])
	{
		j = 0;
		while(tab_couleur[i][j])
		{
			if ((tab_couleur[i][j] < '0' || tab_couleur[i][j] > '9')
				 && (tab_couleur[i][j] != '\n' && tab_couleur[i][j] != ' '))
				return(ft_printf("Error : RGB color value incorrect\n"), NULL);
			j++;
		}
		i++;
	}
	if(i != 3)
		return(ft_printf("Error : color should have type R,G,B\n"), NULL);
	return(tab_couleur);
}

static int	fill_first_struct(t_couleur *couleur, char **tab)
{
	int	i;
	
	i = 0;
	couleur->R = ft_atoi(tab[0]);
	// if (!couleur->R)
	// 	return(1);
	couleur->G = ft_atoi(tab[1]);
	// if (!couleur->G)
	// 	return(1);
	couleur->B = ft_atoi(tab[2]);
	// if (!couleur->B)
	// 	return(1);
	return (0);
}

//on verifie que chaque couleur est dans la range
static int	check_values(t_couleur *couleur)
{
	if(couleur->R < 0 || couleur->R > 255
		|| couleur->G < 0 || couleur->G > 255
		|| couleur->B < 0 || couleur->B > 255)
		return(ft_printf("RGB colors are often in the range [0,255]\n"), 1);
	return (0);
}

//extrait les 3 couleurs (rgb) separees pas une virgule
//converti les str en entiers (atoi)
//on verifie que chaque couleur est dans la range & qu'il n'y a que 3 valeurs, pas de char invalides
//stocke dans la struct
int	parse_color(char *line, t_game *game, int start)
{
	t_couleur	couleur;
	char **tab;
	
	tab = NULL;
	(void) game;
	init_struct_couleur(&couleur);
	tab = extract_color(line, start);
	if (!tab)
		return(1);
	if(fill_first_struct(&couleur, tab))
		return (free_tab(tab), 1);
	if (check_values(&couleur))
	free_tab(tab);
	return (0);
}




// int	fill_first_struct(t_couleur *couleur, char **tab, char *line)
// {
// 	int	i;
// 	int	len;
// 	// int type;		//0 = F et 1 = C
	
// 	i = 0;
// 	while(line[i] && (line[i] == '\t' || line[i] == ' '))
// 		i++;
// 	// if(line[i] == 'F')
// 	// 	type = 0;
// 	// else
// 	// 	type = 1;
// 	// i = 0;
// 	while(tab[i])
// 	{
// 		len = 0;
// 		while(tab[i][len])
// 			len++;
// 		couleur->R = malloc(sizeof(char) * len);
// 		if (!couleur->R)
// 			return(NULL);
// 		couleur->R = ft_strdup()
		 
// 	}
// 	couleur->R 
// }

// int	fill_first_struct(t_couleur *couleur, char **tab)
// {
// 	int	i;
	
// 	i = 0;
// 	while(tab[i])
// 	{
// 		if(i = 1)
// 		{
// 			couleur->R = ft_strdup(tab[i]);
// 			if (!couleur->R)
// 				return(1);			
// 		}
// 		else if (i = 2)
// 		{
// 			couleur->G = ft_strdup(tab[i]);
// 			if (!couleur->G)
// 				return(1);	
// 		}
// 		else if (i = 3)
// 		{
// 			couleur->B = ft_strdup(tab[i]);
// 			if (!couleur->B)
// 				return(1);	
// 		}
// 		i++;
// 	}
// 	return (0);
// }