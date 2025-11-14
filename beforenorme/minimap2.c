#include "cub3D.h"
#include <math.h>

//But : écrire un pixel dans le framebuffer en toute sécurité.
static void mm_safe_px(t_game *g, int x, int y, uint32_t c)
{
    if (x >= 0 && y >= 0 && x < W && y < H)
        put_px(&g->frame, x, y, c);
}

//But : dessiner un rectangle plein (utilisé pour les cases de la mini-map et le fond).
static void mm_draw_rect(t_game *g, int x, int y, int w, int h, uint32_t c)
{
    int i, j;
    j = 0;
    while (j < h)
    {
        i = 0;
        while (i < w)
        {
            mm_safe_px(g, x + i, y + j, c);
            i++;
        }
        j++;
    }
}

//But : dessiner un petit disque (le pion du joueur).
static void mm_draw_circle(t_game *g, int cx, int cy, int r, uint32_t c)
{
    int y = -r;
    while (y <= r)
    {
        int x = -r;
        while (x <= r)
        {
            if (x*x + y*y <= r*r)
                mm_safe_px(g, cx + x, cy + y, c);
            x++;
        }
        y++;
    }
}

//But : tracer un petit trait devant le joueur pour montrer la direction de vue.
static void mm_draw_dir(t_game *g, int x0, int y0, int len, uint32_t c)
{
    double dx = g->dir_x, dy = g->dir_y;
    double x = (double)x0, y = (double)y0;
    int i = 0;
    while (i < len)
    {
        mm_safe_px(g, (int)x, (int)y, c);
        x += dx;
        y += dy;
        i++;
    }
}

//But : composer toute la mini-map et l’afficher en haut-gauche.
void minimap_draw(t_game *g)
{
    const int R = 8;          /* rayon en cases autour du joueur */
    const int T = 6;          /* taille d’une case en pixels */
    const int OX = 8, OY = 8; /* offset écran (haut-gauche) */

    /* fond opaque pour la zone minimap (optionnel) */
    mm_draw_rect(g, OX-2, OY-2, (2*R+1)*T + 4, (2*R+1)*T + 4, 0x80000000);

    int gy = -R;
    while (gy <= R)
    {
        int gx = -R;
        while (gx <= R)
        {
            int mx = (int)g->px + gx;
            int my = (int)g->py + gy;

            /* top-left pixel du carreau à dessiner */
            int sx = OX + (gx + R) * T;
            int sy = OY + (gy + R) * T;

            uint32_t col;
            if (mx < 0 || my < 0 || mx >= g->map_w || my >= g->map_h)
                col = 0xFF202020;                 /* hors-map */
            else if (g->map_int[my][mx] == 1)
                col = 0xFF505050;                 /* mur */
            else
                col = 0xFF9A9A9A;                 /* vide */

            mm_draw_rect(g, sx, sy, T-1, T-1, col);
            gx++;
        }
        gy++;
    }

    /* position du joueur dans la minimap (au centre du patch) */
    int pcx = OX + R*T + (int)((g->px - floor(g->px)) * T);
    int pcy = OY + R*T + (int)((g->py - floor(g->py)) * T);

    /* joueur + direction */
    mm_draw_circle(g, pcx, pcy, 2, 0xFFFF0000);  /* point rouge */
    mm_draw_dir(g, pcx, pcy, 8, 0xFFFF0000);     /* petit trait devant */
}
