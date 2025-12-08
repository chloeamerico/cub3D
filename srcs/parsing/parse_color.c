/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:45:07 by camerico          #+#    #+#             */
/*   Updated: 2025/12/08 15:24:03 by lleichtn         ###   ########.fr       */
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
		if (game->config.type == 1)
			return (ft_printf("Error : Only 1 F and 1 C line needed.\n"), 1);
		game->config.type = 1;
	}
	else if (line[i] == 'C')
	{
		if (game->config.type == 2)
			return (ft_printf("Error : Only 1 F and 1 C line needed.\n"), 1);
		game->config.type = 2;
	}
	return (0);
}

static char	**extract_color(char *line, int i)
{
	char	**tab;
	int		idx;

	while (line[i] == ' ' || line[i] == '\t')
		i++;
	tab = ft_split(line + i, ',');
	if (!tab)
		return (NULL);
	idx = 0;
	while (tab[idx])
	{
		if (is_empty_or_whitespace(tab[idx]))
			return (err1(tab), NULL);
		if (has_invalid_chars(tab[idx]))
			return (err1(tab), NULL);
		idx++;
	}
	if (idx != 3)
		return (err2(tab), NULL);
	return (tab);
}

// static int	fill_first_struct(t_game *game, char **tab)
// {
// 	int	*dest;

// 	if (game->config.type == 1)
// 		dest = game->config.f;
// 	else
// 		dest = game->config.c;
// 	dest[0] = ft_atoi(tab[0]);
// 	dest[1] = ft_atoi(tab[1]);
// 	dest[2] = ft_atoi(tab[2]);
// 	free_char_tab(tab);
// 	return (0);
// }

static int	fill_first_struct(t_game *game, char **tab)
{
	int	*dest;

	if (!tab[0] || !tab[1] || !tab[2]
		|| ft_strlen(tab[0]) > 4
		|| ft_strlen(tab[1]) > 4
		|| ft_strlen(tab[2]) > 5)
	{
		free_char_tab(tab);
		return (ft_printf("Error : RGB value too long\n"), 1);
	}
	if (game->config.type == 1)
		dest = game->config.f;
	else
		dest = game->config.c;
	dest[0] = ft_atoi(tab[0]);
	dest[1] = ft_atoi(tab[1]);
	dest[2] = ft_atoi(tab[2]);
	free_char_tab(tab);
	return (0);
}

static int	check_values(t_config *cfg)
{
	if (cfg->type == 1)
	{
		if (cfg->f[0] < 0 || cfg->f[0] > 255
			|| cfg->f[1] < 0 || cfg->f[1] > 255
			|| cfg->f[2] < 0 || cfg->f[2] > 255)
			return (ft_printf("Error : F colors must be [0,255]\n"), 1);
	}
	else
	{
		if (cfg->c[0] < 0 || cfg->c[0] > 255
			|| cfg->c[1] < 0 || cfg->c[1] > 255
			|| cfg->c[2] < 0 || cfg->c[2] > 255)
			return (ft_printf("Error : C colors must be [0,255]\n"), 1);
	}
	return (0);
}

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
		return (1);
	if (check_values(&game->config))
		return (1);
	return (0);
}
