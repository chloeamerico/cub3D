/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args_and_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:59:25 by camerico          #+#    #+#             */
/*   Updated: 2025/11/14 14:28:36 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//verifie que ce n'est pas seulement .cub
static int	check_extension_cub(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len < 5)
	{
		printf("Error : map sould have type <map.cub>\n");
		return (1);
	}
	if (ft_strcmp(arg + len - 4, ".cub") != 0)
	{
		printf("Error : map doesn't finish with a '.cub'\n");
		return (1);
	}
	return (0);
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

int	check_arg(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Error : number of arguments invalid\n");
		return (1);
	}
	if (check_extension_cub(argv[1]))
		return (1);
	if (check_file_exist(argv[1]))
		return (1);
	return (0);
}

// ouvre le fichier, lit le fichier .cub ligne par ligne,
// et le transforme en tableau char **
static char	**load_file(char *name_map)
{
	char	**file;
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(name_map, O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), NULL);
	file = malloc(sizeof(char *) * 100);
	if (!file)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		file[i++] = line;
		line = get_next_line(fd);
	}
	file[i] = NULL;
	return (close(fd), file);
}

// static void	init_struct_tab(t_game *game)
// {
// 	game->config->C[0]	
// }

//fonciton poru initialiser les variables de la structure
int	init_struct(t_game *game, char **argv)
{
	int	i;

	i = 0;
	game->file_map = load_file(argv[1]);
	game->config = malloc(sizeof(t_config));
	if (!game->config)
		return (1);
	game->config->no_texture = NULL;
	game->config->so_texture = NULL;
	game->config->we_texture = NULL;
	game->config->ea_texture = NULL;
	while (i <= 2)
	{
		game->config->c[i] = 0;
		i++;
	}
	i = 0;
	while (i <= 2)
	{
		game->config->f[i] = 0;
		i++;
	}
	game->config->type = 0;
	return (0);
}
