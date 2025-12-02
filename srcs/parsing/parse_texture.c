/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:40:29 by camerico          #+#    #+#             */
/*   Updated: 2025/12/02 18:48:04 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_extension_xpm(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (ft_strcmp(path + len - 4, ".xpm") != 0)
	{
		printf("Error : texture doesn't finish with a '.xpm'\n");
		return (1);
	}
	return (0);
}

//extrait le chemin vers la texture
static char	*find_texture_path(char *line, int i, char *path)
{
	int	len;
	int	start;

	len = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	start = i;
	while (line[i] && line[i] != ' ' && line[i] != '\n')
	{
		len++;
		i++;
	}
	path = malloc(sizeof(char) * (len + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[start] && line[start] != ' ' && line[start] != '\n')
	{
		path[i] = line[start];
		start++;
		i++;
	}
	path[i] = '\0';
	return (path);
}

// static int	add_struct(t_game *game, char *path, char *line, int i)
// {
// 	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
// 	{
// 		if (game->config.no_texture != NULL)
// 			return (ft_printf("Error : double North texture detected\n"), 1);
// 		game->config.no_texture = path;
// 	}
// 	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
// 	{
// 		if (game->config.so_texture != NULL)
// 			return (ft_printf("Error : double South texture detected\n"), 1);
// 		game->config.so_texture = path;
// 	}
// 	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
// 	{
// 		if (game->config.we_texture != NULL)
// 			return (ft_printf("Error : double West texture detected\n"), 1);
// 		game->config.we_texture = path;
// 	}
// 	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
// 	{
// 		if (game->config.ea_texture != NULL)
// 			return (ft_printf("Error : double East texture detected\n"), 1);
// 		game->config.ea_texture = path;
// 	}
// 	return (0);
// }

// static int	add_struct(t_game *game, char *path, char *line, int i)
// {
// 	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
// 	{
// 		if (game->config.no_texture != NULL)
// 			return (free(path), free(game->config.no_texture),
// 				game->config.no_texture = NULL,
// 				ft_printf("Error : double North texture detected\n"), 1);
// 		game->config.no_texture = path;
// 	}
// 	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
// 	{
// 		if (game->config.so_texture != NULL)
// 			return (free(path), free(game->config.so_texture),
// 				game->config.so_texture = NULL,
// 				ft_printf("Error : double South texture detected\n"), 1);
// 		game->config.so_texture = path;
// 	}
// 	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
// 	{
// 		if (game->config.we_texture != NULL)
// 			return (free(path), free(game->config.we_texture),
// 				game->config.we_texture = NULL,
// 				ft_printf("Error : double West texture detected\n"), 1);
// 		game->config.we_texture = path;
// 	}
// 	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
// 	{
// 		if (game->config.ea_texture != NULL)
// 			return (free(path), free(game->config.ea_texture),
// 				game->config.ea_texture = NULL,
// 				ft_printf("Error : double East texture detected\n"), 1);
// 		game->config.ea_texture = path;
// 	}
// 	return (0);
// }

//extrait le chemin vers la texture
// verifie que le fichier existe (avec open)
//verifie l'extension xpm
// l'ajoute a la structure
int	parse_texture(char *line, int i, t_game *game)
{
	char	*path;
	int		start;

	start = 0;
	path = find_texture_path(line, i, NULL);
	if (!path)
		return (1);
	if (check_file_exist(path))
		return (free(path), 1);
	if (check_extension_xpm(path))
		return (free(path), 1);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (add_struct(game, path, line, start))
		return (1);
	return (0);
}
