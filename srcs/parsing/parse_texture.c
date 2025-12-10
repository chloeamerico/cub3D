/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 18:40:29 by camerico          #+#    #+#             */
/*   Updated: 2025/12/10 15:29:34 by camerico         ###   ########.fr       */
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

int	check_file_exist(char *name)
{
	int	fd;

	fd = open(name, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error : opening the file, wrong path %s\n", name);
		return (1);
	}
	close(fd);
	return (0);
}

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
