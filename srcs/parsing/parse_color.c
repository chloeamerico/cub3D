/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:45:07 by camerico          #+#    #+#             */
/*   Updated: 2025/11/14 14:29:05 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	find_type(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'F')
	{
		if (game->config->type == 1)
			return (ft_printf("Error1 : Only 1 F and 1 C line needed.\n"), 1);
		game->config->type = 1;
	}
	else if (line[i] == 'C')
	{
		if (game->config->type == 2)
			return (ft_printf("Error2 : Only 1 F and 1 C line needed.\n"), 1);
		game->config->type = 2;
	}
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

//fait un split pour extraire les valeurs dans un tab
// on verifie qu'il n'y ait que 3 valeurs
static char	**extract_color(char *line, int i)
{
	char	**tab_couleur;
	int		j;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	tab_couleur = ft_split(line + i, ',');
	if (!tab_couleur)
		return (NULL);
	i = 0;
	while (tab_couleur[i])
	{
		j = 0;
		while (tab_couleur[i][j])
		{
			if ((tab_couleur[i][j] < '0' || tab_couleur[i][j] > '9')
				&& (tab_couleur[i][j] != '\n' && tab_couleur[i][j] != ' '))
				return (err1(tab_couleur), NULL);
			j++;
		}
		i++;
	}
	if (i != 3)
		return (err2(tab_couleur), NULL);
	return (tab_couleur);
}

static int	fill_first_struct(t_game *game, char **tab)
{
	int	i;

	i = 0;
	if (game->config->type == 1)
	{
		if (game->config->f[0] != 0)
			return (ft_printf("Error : Only one F and one C line needed.\n"), 1);
		i = 0;
		while (tab[i])
		{
			game->config->f[i] = ft_atoi(tab[i]);
			i++;
		}
	}
	else
	{
		if (game->config->c[0] != 0)
			return (ft_printf("Error : Only one F and one C line needed.\n"), 1);
		i = 0;
		while (tab[i])
		{
			game->config->c[i] = ft_atoi(tab[i]);
			i++;
		}
	}
	free_char_tab(tab);
	return (0);
}

//on verifie que chaque couleur est dans la range
static int	check_values(t_config *config)
{
	if (config->type == 1)
	{
		if ((config->f[0] < 0 || config->f[0] > 255)
			|| (config->f[1] < 0 || config->f[1] > 255)
			|| (config->f[2] < 0 | config->f[2] > 255))
			return (ft_printf("RGB colors are often in the range [0,255]\n"), 1);
	}
	if (config->type == 2)
	{
		if ((config->c[0] < 0 || config->c[0] > 255)
			|| (config->c[1] < 0 || config->c[1] > 255)
			|| (config->c[2] < 0 || config->c[2] > 255))
			return (ft_printf("RGB colors are often in the range [0,255]\n"), 1);
	}
	return (0);
}

//extrait les 3 couleurs (rgb) separees pas une virgule
//converti les str en entiers (atoi)
//on verifie que chaque couleur est dans la range & qu'il n'y a que 3 valeurs,
//pas de char invalides
//stocke dans la struct
int	parse_color(char *line, t_game *game, int start)
{
	char	**tab;

	tab = NULL;
	if (find_type(game, line))
		return (1);
	tab = extract_color(line, start);
	if (!tab)
		return (1);
	if (fill_first_struct(game, tab))
		return (free_char_tab(tab), 1);
	if (check_values(game->config))
		return (1);
	return (0);
}
