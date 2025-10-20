/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:54:42 by camerico          #+#    #+#             */
/*   Updated: 2025/10/20 10:27:26 by lleichtn         ###   ########.fr       */
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

int check_arg(int argc, char **argv);
int	init_struct(t_game *game, char **argv);
char	**load_map(char *name_map);
int divide_map_config(t_game *game);

void	free_map(char **map);

/* ************************************************************************** */
/* STRUCTURES                                                                 */
/* ************************************************************************** */

typedef struct	s_game
{
	char	**file_map;		//tout le fichier .cub transforme en char **
	char	**map;			//que la map
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



/* ************************************************************************** */
/* DEBUG                                                                      */
/* ************************************************************************** */

#endif