/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:54:42 by camerico          #+#    #+#             */
/*   Updated: 2025/10/16 18:59:50 by camerico         ###   ########.fr       */
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

typedef struct	t_couleur
{
	char	R;
	char	G;
	char	B;
	int		int_r;
	int		int_g;
	int		int_b;
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

void	free_map(char **map);


/* ************************************************************************** */
/* DEBUG                                                                      */
/* ************************************************************************** */

#endif