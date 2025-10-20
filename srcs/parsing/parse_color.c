/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:45:07 by camerico          #+#    #+#             */
/*   Updated: 2025/10/20 15:21:41 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// //fonctionne pour eviter les double A ou F, mais cree des pb valgrind
// static int init_struct_couleur(t_couleur *couleur, char *line)
// {
// 	int i;

// 	i = 0;
// 	while(line[i] && (line[i] == ' ' || line[i] == '\t'))
// 		i++;
// 	if(line[i] == 'F')
// 	{
// 		// if(couleur->F == 1)
// 		// 	return(ft_printf("Error : Only one F and one C line needed.\n"), 1);
// 		couleur->F = 1;
// 		couleur->C = 0;
// 	}
// 	if(line[i] == 'C')
// 	{
// 		// if(couleur->C == 1)
// 		// 	return(ft_printf("Error : Only one F and one C line needed.\n"), 1);
// 		couleur->C = 1;
// 		couleur->F = 0;
// 	}
// 	couleur->R = 0;
// 	couleur->G = 0;
// 	couleur->B = 0;
// 	return (0);
// }

static int find_type(t_game *game, char *line)
{
	int	i;

	i = 0;
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	if(line[i] == 'F')
	{
		if (game->config->type == 1)
			return(ft_printf("Error1 : Only one F and one C line needed.\n"), 1);
		game->config->type = 1;
	}
	else if(line[i] == 'C')
	{
		if (game->config->type == 2)
			return(ft_printf("Error2 : Only one F and one C line needed.\n"), 1);
		game->config->type = 2;
		printf("%i\n", game->config->type);
	}
	return (0);
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

static int	fill_first_struct(t_game *game, char **tab)
{
	int	i;

	i = 0;
	if(game->config->type == 1)
	{
		if(game->config->F[0] != 0)
			return(ft_printf("Error : Only one F and one C line needed.\n"), 1);
		i = 0;
		while(tab[i])
		{
			game->config->F[i] = ft_atoi(tab[i]);
			i++;
		}
	}
	else
	{
		if(game->config->C[0] != 0)
			return(ft_printf("Error : Only one F and one C line needed.\n"), 1);
		i = 0;
		while(tab[i])
		{
			game->config->C[i] = ft_atoi(tab[i]);
			i++;
		}
	}
	free_tab(tab);
	return (0);
}

//on verifie que chaque couleur est dans la range
static int	check_values(t_config *config)
{
	if(config->type == 1)
	{
		if (config->F[0] < 0 || config->F[0] > 255
		|| config->F[0] < 0 || config->F[0] > 255
		|| config->F[0] < 0 || config->F[0] > 255)
			return(ft_printf("RGB colors are often in the range [0,255]\n"), 1);
	}
	if(config->type == 2)
		{
		if (config->C[0] < 0 || config->C[0] > 255
		|| config->C[0] < 0 || config->C[0] > 255
		|| config->C[0] < 0 || config->C[0] > 255)
			return(ft_printf("RGB colors are often in the range [0,255]\n"), 1);
	}
	return (0);
}

// int	fill_sec_struct(t_couleur *couleur, t_game *game, char *str)
// {
// 	int	type;		//F = 0 et C = 1
// 	int i;

// 	i = 0;
// 	if ()
// }

//extrait les 3 couleurs (rgb) separees pas une virgule
//converti les str en entiers (atoi)
//on verifie que chaque couleur est dans la range & qu'il n'y a que 3 valeurs, pas de char invalides
//stocke dans la struct
int	parse_color(char *line, t_game *game, int start)
{
	char **tab;
	
	tab = NULL;
	
	// if(init_struct_couleur(&couleur, line))
	// 	return (1);
	// printf("apres premiere ligne tab C : %i, %i, %i\n", game->config->C[0], game->config->C[1], game->config->C[2]);
	// printf("apres premiere ligne tab F : %i, %i, %i\n", game->config->F[0], game->config->F[1], game->config->F[2]);
	
	if (find_type(game, line))
		return (1);
	printf("type : %i\n", game->config->type);
	tab = extract_color(line, start);
	if (!tab)
		return(free_tab(tab), 1);
	if(fill_first_struct(game, tab))
		return (free_tab(tab), 1);
	if (check_values(game->config))
		return(1);
	printf("apres premiere ligne tab C : %i, %i, %i\n", game->config->C[0], game->config->C[1], game->config->C[2]);
	printf("apres premiere ligne tab F : %i, %i, %i\n", game->config->F[0], game->config->F[1], game->config->F[2]);
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