/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:52:02 by camerico          #+#    #+#             */
/*   Updated: 2025/10/15 16:06:34 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// ouvre le fichier, lit la map ligne par ligne, et la transforme en tableau
char	**load_map(char *name_map)
{
	char	**map;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(name_map, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening map"), NULL);
	map = malloc(sizeof(char *) * 100);
	if (!map)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		map[i++] = line;
		line = get_next_line(fd);
	}
	map[i] = NULL;
	return (close(fd), map);
}

