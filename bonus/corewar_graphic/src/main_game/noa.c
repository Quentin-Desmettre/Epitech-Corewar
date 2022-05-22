/*
** EPITECH PROJECT, 2021
** corewar_graphic
** File description:
** noa.c
*/

#include "rpg.h"
#include "op.h"

void set_selector_color(graphic_war_t *g, int color)
{
    sfColor colors[4] = {{0, 255, 68, 255}, {255, 0, 234, 255}, {0, 200, 255, 255}, {255, 0, 4, 255}};

    sfRectangleShape_setFillColor(g->rect, colors[color]);
}

void set_square_color(graphic_war_t *g, int index)
{
    sfColor colors[5] = {sfBlack, {0, 69, 18 * 2, 255}, {59 * 2, 0, 54 * 2, 255}, {1, 0, 89 * 2, 255}, {61 * 2, 0, 1, 255}};
    int color = g->graph->color[g->graph->current_cycle][index];

    if (color >= 10)
        set_selector_color(g, color - 11);
    else
        sfRectangleShape_setFillColor(g->rect, colors[color]);
}

void set_letter(graphic_war_t *g, int index)
{
    unsigned char letters = g->graph->bytes[g->graph->current_cycle][index];
    char *str = unsigned_to_str_base(letters, "0123456789ABCDEF");

    if (strlen(str) == 1) {
        str = realloc(str, 3);
        str[1] = str[0];
        str[0] = '0';
        str[2] = '\0';
    }
    sfText_setString(g->byte, str);
    free(str);
}

void draw_graph(graphic_war_t *g)
{
    int index = 0;
    sfRenderTexture_clear(g->rtex, sfBlack);
    sfVector2u size = sfRenderTexture_getSize(g->rtex);
    float offset = size.y - (size.x / 8.0 * 96);
    sfVector2f pos = {0, offset / 2};

    for (int j = 0; j < 64; j++) {
        for (int i = 0; i < 96; i++) {
            set_square_color(g, index);
            set_letter(g, index);
            sfText_setPosition(g->byte, (sfVector2f){pos.x + 5, pos.y + 5});
            sfRectangleShape_setPosition(g->rect, pos);
            sfRenderTexture_drawRectangleShape(g->rtex, g->rect, 0);
            sfRenderTexture_drawText(g->rtex, g->byte, 0);
            pos.x += size.x / 7.0;
            index++;
        }
        pos.x = 0;
        pos.y += size.x / 7.0;
    }
    sfRenderTexture_display(g->rtex);
}

void camera_move_mouse(graphic_war_t *g)
{
    sfRenderWindow *windows = window(NULL)->win;
    sfVector2i mpos = sfMouse_getPositionRenderWindow(windows);
    sfVector2f pos;

    if (!g->oldMousePos.x && !g->oldMousePos.y)
        g->oldMousePos = sfMouse_getPositionRenderWindow(windows);
    pos = (sfVector2f) {(float)g->oldMousePos.x -
    (float)mpos.x, (float)g->oldMousePos.y - (float)mpos.y};
    sfView_move(g->view, (sfVector2f){pos.x * g->zoom, pos.y * g->zoom});
    g->oldMousePos = sfMouse_getPositionRenderWindow(windows);
}

void ingame_zoom(graphic_war_t *g, sfEvent ev)
{
    if (ev.type != sfEvtMouseWheelScrolled) {
        sfRenderTexture_setView(g->rtex, g->view);
        return;
    }
    if (ev.mouseWheelScroll.delta < 0.0) {
        sfView_zoom(g->view, (float)(1.0 / 1.1));
        g->zoom *= (float)(1.0 / 1.1);
    }
    else if (ev.mouseWheelScroll.delta > 0.0) {
        sfView_zoom(g->view, (float)1.1);
        g->zoom *= 1.1;
    }
    sfRenderTexture_setView(g->rtex, g->view);
}

void graph_ev(graphic_war_t *g, sfEvent ev)
{
    static int need_moove = 0;
    if (ev.type == sfEvtMouseButtonPressed &&
        ev.mouseButton.button == sfMouseLeft)
        need_moove = 1;
    if (ev.type == sfEvtMouseButtonReleased &&
        ev.mouseButton.button == sfMouseLeft) {
        g->oldMousePos = (sfVector2i){0, 0};
        need_moove = 0;
        }
    if (need_moove)
        camera_move_mouse(g);
    ingame_zoom(g, ev);
}

graphic_war_t *create_graphic_war(sfVector2f size, corewar_grap_t *graph)
{
    graphic_war_t *g = malloc(sizeof(graphic_war_t));

    g->rtex = sfRenderTexture_create(size.x, size.y, 0);
    g->view = sfView_copy(sfRenderTexture_getView(g->rtex));
    sfRenderTexture_setView(g->rtex, g->view);
    graph->current_cycle = 0;
    g->graph = graph;
    g->byte = init_text("", (size.x / 8) / 1.5);
    g->rect = create_rectangle((sfVector2f){size.x / 8, size.x / 8}, sfRed, 0, sfWhite);
    sfRectangleShape_setPosition(g->rect, (sfVector2f){0, 0});
    sfText_setColor(g->byte, sfWhite);
    g->oldMousePos = (sfVector2i){0, 0};
    sfView_zoom(g->view, (float)25);
    sfView_move(g->view, (sfVector2f){size.x * 5, size.y * 5});
    sfRenderTexture_setView(g->rtex, g->view);
    g->zoom = 25;
    return (g);
}
