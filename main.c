/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lleichtn <lleichtn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:16:14 by lleichtn          #+#    #+#             */
/*   Updated: 2025/11/14 14:16:28 by lleichtn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h"
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

/* externs de ton projet */
extern int   init_mlx(t_game *g);
extern int   frame_new(t_game *g, int w, int h);
// extern int   render_frame(t_game *g);
extern void  player_update(t_game *g, double dt);
extern int   key_press(int k, t_game *g);
extern int   key_release(int k, t_game *g);
extern int   mouse_press(int b, int x, int y, t_game *g);
extern int   mouse_release(int b, int x, int y, t_game *g);
extern int   mouse_move(int x, int y, t_game *g);
extern int   close_win(t_game *g);
extern int   load_textures(t_game *g, const char *no, const char *so, const char *we, const char *ea);
extern int   load_floor_texture(t_game *g, const char *path);

/* parsing */
extern int   check_arg(int ac, char **av);
extern int   init_struct(t_game *g, char **av);
extern int   divide_map_config(t_game *g);
extern int   parsing_map(t_game *g);

/* --- helpers --- */
static inline uint32_t argb_u32(int a,int r,int g,int b){
    if(a<0)a=0; if(a>255)a=255;
    if(r<0)r=0; if(r>255)r=255;
    if(g<0)g=0; if(g>255)g=255;
    if(b<0)b=0; if(b>255)b=255;
    return ((uint32_t)a<<24)|((uint32_t)r<<16)|((uint32_t)g<<8)|(uint32_t)b;
}

static int **map_char_to_int(char **map, int w, int h)
{
    int **m = (int**)malloc(sizeof(int*) * h);
    if(!m) return NULL;
    for(int y=0; y<h; ++y){
        m[y] = (int*)malloc(sizeof(int) * w);
        if(!m[y]) return NULL;
        for(int x=0; x<w; ++x){
            char c = map[y][x];
            /* murs: '1' et ' ' ; vide: '0' + start NSEW */
            m[y][x] = (c == '1' || c == ' ') ? 1 : 0;
        }
    }
    return m;
}

static void set_player_from_map_char(t_game *g)
{
    for(int y=0; y<g->map_h; ++y){
        for(int x=0; x<g->map_w; ++x){
            char c = g->map[y][x];
            if (c=='N'||c=='S'||c=='E'||c=='W')
            {
                g->px = x + 0.5;
                g->py = y + 0.5;
                if (c=='N'){ g->dir_x=0;  g->dir_y=-1; g->pl_x= 0.66; g->pl_y=0;    }
                if (c=='S'){ g->dir_x=0;  g->dir_y= 1; g->pl_x=-0.66; g->pl_y=0;    }
                if (c=='E'){ g->dir_x=1;  g->dir_y= 0; g->pl_x= 0.0;  g->pl_y=0.66; }
                if (c=='W'){ g->dir_x=-1; g->dir_y= 0; g->pl_x= 0.0;  g->pl_y=-0.66;}
                return;
            }
        }
    }
    /* fallback si pas de lettre trouvée */
    g->px = 2.5; g->py = 2.5;
    g->dir_x = -1; g->dir_y = 0; g->pl_x = 0; g->pl_y = -0.66;
}

static double get_time_sec(void){
    struct timeval tv; gettimeofday(&tv,NULL);
    return tv.tv_sec + tv.tv_usec/1000000.0;
}

static int loop_hook(t_game *g){
    static double t0=0.0; double t1=get_time_sec(); if(t0==0.0) t0=t1;
    double dt=t1-t0; t0=t1;
    player_update(g, dt);
    render_frame(g);
    return 0;
}

/* frees simples */
void free_char_tab(char **tab){
    if(!tab) return; for(int i=0; tab[i]; ++i) free(tab[i]); free(tab);
}
void free_int_tab(int **tab, int h){
    if(!tab) return; for(int i=0;i<h;++i) free(tab[i]); free(tab);
}
static void free_all_local(t_game *g){
    if(!g) return;
    free_char_tab(g->file_map);
    free_char_tab(g->map);
    if(g->map_int) free_int_tab(g->map_int, g->map_h);
    if(g->config) free(g->config);
    if(g->data) free(g->data);
}

/* --- MAIN --- */
int main(int ac, char **av, char **envp)
{
    t_game g;

    (void)envp;
    memset(&g, 0, sizeof(g));
    g.mouse_sens = 0.0025;

    /* 1) Parsing du fichier .cub indiqué en paramètre */
    if (check_arg(ac, av)) return 1;
    if (init_struct(&g, av)) { free_all_local(&g); return 1; }
    if (divide_map_config(&g)) { free_all_local(&g); return 1; }
    if (parsing_map(&g)) { free_all_local(&g); return 1; }

    /* dimensions + conversions */
    g.map_w = g.data->map_width;
    g.map_h = g.data->map_height;
    g.map_int = map_char_to_int(g.map, g.map_w, g.map_h);
    if (!g.map_int) { free_all_local(&g); return 1; }

    /* position & orientation depuis la map (N/S/E/W) */
    set_player_from_map_char(&g);

    /* couleurs : ciel BLEU, sol peu importe (sol texturé) */
    g.ceil_col  = argb_u32(255, 0x87, 0xCE, 0xEB);   /* SkyBlue */
    g.floor_col = argb_u32(255, 0x44, 0x44, 0x44);   /* fallback si pas de texture */

    /* 2) Initialisation MLX et frame */
    if (!init_mlx(&g) || !frame_new(&g, W, H)) { free_all_local(&g); return 1; }

    /* 3) Textures murs (toutes = castle.xpm) + sol (grass.xpm) */
	if (!load_textures(&g,
        "texture/sud.xpm",
        "texture/nord.xpm",
        "texture/ouest.xpm",
        "texture/est.xpm"))
    {
        free_all_local(&g); return 1;
    }
    (void)load_floor_texture(&g, "texture/grass.xpm"); /* si échec: le code peindra floor_col */

    /* on peut libérer le gros buffer du fichier texte */
    free_char_tab(g.file_map); g.file_map = NULL;

    /* 4) Hooks & boucle principale */
    memset(g.key, 0, sizeof(g.key));
    mlx_hook(g.win, 17, 0, close_win, &g);
    mlx_hook(g.win, 2, 1L<<0, key_press, &g);
    mlx_hook(g.win, 3, 1L<<1, key_release, &g);
    mlx_hook(g.win, 4, 1L<<2, mouse_press, &g);
    mlx_hook(g.win, 5, 1L<<3, mouse_release, &g);
    mlx_hook(g.win, 6, 1L<<6, mouse_move, &g);
    mlx_loop_hook(g.mlx, loop_hook, &g);
    mlx_loop(g.mlx);

    free_all_local(&g);
    return 0;
}
