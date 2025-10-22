/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:54:42 by camerico          #+#    #+#             */
/*   Updated: 2025/10/22 16:53:05 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/* INCLUDES                                                                   */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <strings.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>
# include "./libft/includes/libft.h"

/* ************************************************************************** */
/* DEFINES                                                                    */
/* ************************************************************************** */

/* ************************************************************************** */
/* STRUCTURES                                                                 */
/* ************************************************************************** */

// typedef struct	t_couleur
// {
// 	int	R;
// 	int	G;
// 	int	B;
// 	int F;		//pour savoir si le type F ou C a deja ete detecte
// 	int	C;
// }	t_couleur;

typedef struct s_data
{
	int 	map_width;      // largeur carte
	int 	map_height;     // hauteur carte
	int 	player_x;       // position X du joueur
	int 	player_y;       // position Y du joueur
	char 	player_dir;    // direction (N/S/E/W)
}	t_data;

typedef struct	s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		type;			//au debut 0, 1 si F , 2 si C
	int		F[3];			//couleur du sol (floor)
	int		C[3];			//couleur du ciel
}	t_config;

typedef struct	s_game
{
	char		**file_map;		//tout le fichier .cub transforme en char **
	char		**map;			//que la map
	t_config	*config;
	t_data		*data;
}	t_game;

/* ************************************************************************** */
/* PROTO                                                                      */
/* ************************************************************************** */

int 	check_arg(int argc, char **argv);
int		init_struct(t_game *game, char **argv);
int 	divide_map_config(t_game *game);
int		parse_config_line(char *line, t_game *game);
int	is_empty_line(char *line);
// char	*find_texture_path(char *line, int i, char *path);
int		check_file_exist(char *name);
int		parse_texture(char *line, int i, t_game *game);
int		parse_color(char *line, t_game *game, int start);
int extract_map(t_game *game, int line_map_start);
int	parsing_map(t_game *game);
int	check_map_close(t_game *game, char **map);
int	valid_path(t_game *game);

void	free_tab(char **tab);


/* ************************************************************************** */
/* DEBUG                                                                      */
/* ************************************************************************** */

#endif