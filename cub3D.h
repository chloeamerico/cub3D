/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:54:42 by camerico          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/10/20 10:27:26 by lleichtn         ###   ########.fr       */
=======
/*   Updated: 2025/10/17 15:36:45 by camerico         ###   ########.fr       */
>>>>>>> origin
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
# include <stddef.h>

/* ************************************************************************** */
/* DEFINES                                                                    */
/* ************************************************************************** */

/* ************************************************************************** */
/* STRUCTURES                                                                 */
/* ************************************************************************** */

typedef struct	t_couleur
{
	int	R;
	int	G;
	int	B;
}	t_couleur;

typedef struct	s_config
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		F[3];			//couleur du sol (floor)
	int		C[3];			//couleur du ciel
}	t_config;

typedef struct	s_game
{
	char		**file_map;		//tout le fichier .cub transforme en char **
	char		**map;			//que la map
	t_config	*config;
}	t_game;

typedef struct s_config {
    char *north_texture;
    char *south_texture;
    char *west_texture;
    char *east_texture;
    int   floor_rgb[3];
    int   ceiling_rgb[3];
    int   has_no, has_so, has_we, has_ea;
    int   has_f,  has_c;
    int   config_complete;
} t_config;

/* ************************************************************************** */
/* PROTO                                                                      */
/* ************************************************************************** */

int 	check_arg(int argc, char **argv);
int		init_struct(t_game *game, char **argv);
int 	divide_map_config(t_game *game);
int		parse_config_line(char *line, t_game *game);
// char	*find_texture_path(char *line, int i, char *path);
int		check_file_exist(char *name);
int		parse_texture(char *line, int i, t_game *game);
int		parse_color(char *line, t_game *game, int start);

void	free_tab(char **tab);


/* ************************************************************************** */
/* DEBUG                                                                      */
/* ************************************************************************** */

#endif