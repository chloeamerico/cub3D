/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:54:42 by camerico          #+#    #+#             */
/*   Updated: 2025/11/04 16:41:50 by camerico         ###   ########.fr       */
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

typedef struct s_minimap
{
	int width;        // largeur  minimap (en pixels)
    int height;       // hauteur  minimap (en pixels)
    int case_size;    // taille d'une case de la carte (en pixels) --> + c'est grand, + la minimap prendra de place a l'ecran
    int location_x;     // coordonees X du coint en haut a gauche de la minimap
    int location_y;     // coordonees Y du coint en haut a gauche de la minimap
    // int scale;        // facteur echelle pour afficher la minimap
}	t_minimap;

typedef struct s_data_mini
{
	void	*img;
	char	*address;
	int		bpp;
	int		line_len;
}	t_data_mini;

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
	t_minimap	*mini;
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