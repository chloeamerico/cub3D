/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: camerico <camerico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 15:12:52 by camerico          #+#    #+#             */
/*   Updated: 2025/12/02 15:13:39 by camerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/* INCLUDES */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include "mlx.h"
# include "./libft/includes/libft.h"
# include <X11/keysym.h>
# include <math.h>
# include <sys/time.h>

/* ************************************************************************** */
/* DEFINES */
/* ************************************************************************** */

# define W 1024
# define H 640

/* ************************************************************************** */
/* STRUCTURES */
/* ************************************************************************** */

typedef struct s_pair
{
	const char	*a;
	const char	*b;
}	t_pair;

typedef struct s_data
{
	int			map_width;
	int			map_height;
	int			player_x;
	int			player_y;
	char		player_dir;
}	t_data;

typedef struct s_config
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			type;
	int			f[3];
	int			c[3];
}	t_config;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			w;
	int			h;
}	t_img;

typedef struct s_tex
{
	t_img		i;
}	t_tex;

typedef struct s_ray
{
	double		cam_x;
	double		ray_x;
	double		ray_y;
	int			map_x;
	int			map_y;
	double		side_x;
	double		side_y;
	double		delta_x;
	double		delta_y;
	int			step_x;
	int			step_y;
	int			side;
	double		perp;
}	t_ray;

typedef struct s_game
{
	char		**file_map;
	char		**map;

	t_config	config;
	t_data		*data;

	void		*mlx;
	void		*win;

	t_img		frame;

	t_tex		floor_tex;
	t_tex		tex_no;
	t_tex		tex_so;
	t_tex		tex_we;
	t_tex		tex_ea;

	int			**map_int;
	int			map_w;
	int			map_h;

	double		px;
	double		py;
	double		dir_x;
	double		dir_y;
	double		pl_x;
	double		pl_y;

	uint32_t	ceil_col;
	uint32_t	floor_col;

	int			key[65536];
	double		mouse_sens;
	int			mouse_captured;
}	t_game;

//minimap struct

typedef struct s_mm_rect
{
	int			x;
	int			y;
	int			w;
	int			h;
}	t_mm_rect;

typedef struct s_mm_circle
{
	int			x;
	int			y;
	int			r;
	uint32_t	col;
}	t_mm_circle;

typedef struct s_mm_dir
{
	int			x;
	int			y;
	int			len;
	uint32_t	col;
}	t_mm_dir;

/* ************************************************************************** */
/* PARSING */
/* ************************************************************************** */

int			check_arg(int argc, char **argv);
int			init_struct(t_game *game, char **argv);
int			divide_map_config(t_game *game);
int			parse_config_line(char *line, t_game *game);
int			is_empty_line(char *line);
int			check_file_exist(char *name);
int			parse_texture(char *line, int i, t_game *game);
int			parse_color(char *line, t_game *game, int start);
int			extract_map(t_game *game, int line_start);
int			parsing_map(t_game *game);
int			check_map_close(t_game *game, char **map);
int			valid_path(t_game *game);
int			check_cub_char_invalid(char *line, int nb_conf);
int			implement_config_line(t_game *game, int *nb_conf, int i);
void		free_char_tab(char **tab);
void		free_int_tab(int **tab, int height);
void		err1(char **tab);
void		err2(char **tab);

/* ************************************************************************** */
/* RAYCASTING & RENDER */
/* ************************************************************************** */

int			init_mlx(t_game *g);
int			frame_new(t_game *g, int w, int h);
void		frame_destroy(t_game *g);
void		put_px(t_img *i, int x, int y, uint32_t c);

uint32_t	get_texel(const t_tex *t, int u, int v);

void		ray_dda(t_game *g, t_ray *r);

void		draw_column(t_game *g, int x, t_ray *r);

int			key_press(int key, t_game *g);
int			key_release(int key, t_game *g);
int			close_win(t_game *g);
void		player_update(t_game *g, double dt);
int			mouse_press(int button, int x, int y, t_game *g);
int			mouse_release(int button, int x, int y, t_game *g);
int			mouse_move(int x, int y, t_game *g);
void		rotate_player(t_game *g, double a);
void		center_mouse(t_game *g);
void		player_rotate_keys(t_game *g, double dt);

int			load_floor_texture(t_game *g, const char *path);
int			load_one(t_game *g, t_tex *t, const char *path);
int			load_wall_textures(t_game *g);
t_tex		*choose_texture(t_game *g, t_ray *r);
void		draw_walls(t_game *g, int x, t_ray *r, t_tex *tex);

void		render_frame(t_game *g);
void		minimap_draw(t_game *g);

void		free_mlx(t_game *g);
void		free_all_local(t_game *g);

// minimap 

void		mm_draw_circle(t_game *g, t_mm_circle c);
void		mm_draw_dir(t_game *g, t_mm_dir d);
void		mm_safe_px(t_game *g, int x, int y, uint32_t col);
void		mm_draw_rect(t_game *g, t_mm_rect r, uint32_t col);

#endif
