/*
** EPITECH PROJECT, 2021
** corewar_graphic
** File description:
** quentin.c
*/

#include "rpg.h"

#define CYCLE_PER_SEC 1000

const sfTexture *draw_main_play(window_t *win)
{
    main_play_t *m = win->menus[MAIN];
    sfVector2f size = win_size(win);
    static sfClock *c = NULL;

    if (!c)
        c = sfClock_create();
    if (sfClock_getElapsedTime(c).microseconds > 1000000.0 / CYCLE_PER_SEC) {
        if (m->war->graph->current_cycle < m->war->graph->nbr_cycle_max)
            m->war->graph->current_cycle++;
        sfClock_restart(c);
    }

    sfRenderTexture_clear(m->rtex, sfBlack);

    draw_graph(m->war);
    sfSprite *s = init_sprite_from_texture(sfRenderTexture_getTexture(m->war->rtex));
    sfRenderTexture_drawSprite(m->rtex, s, NULL);
    sfSprite_destroy(s);

    for (int i = 0; m->champ_names[i]; i++) {
        sfSprite_setPosition(m->box, (sfVector2f){size.x * 0.65, size.y * 0.03 + size.y * 0.22 * i});
        sfRenderTexture_drawSprite(m->rtex, m->box, NULL);
        sfRenderTexture_drawText(m->rtex, m->champ_names[i], NULL);
    }
    for (int i = 0; i < 3; i++)
        draw_button_to_rtex(m->buttons[i], m->rtex);
    sfRenderTexture_display(m->rtex);
    return sfRenderTexture_getTexture(m->rtex);
}

void main_play_ev(window_t *win, sfEvent ev)
{
    main_play_t *m = win->menus[MAIN];

    if (ev.type == sfEvtMouseMoved)
        check_button_move(m->buttons, 3, ev.mouseMove.x, ev.mouseMove.y);
    if (ev.type == sfEvtMouseButtonPressed)
        check_button_press(m->buttons, 3, ev.mouseButton.x, ev.mouseButton.y);
    if (ev.type == sfEvtMouseButtonReleased)
        check_button_release(m->buttons, 3,
        (sfVector2f){ev.mouseButton.x, ev.mouseButton.y}, win);
    graph_ev(m->war, ev);
}

void pause_cycle(void *win)
{
    window_t *w = win;
    main_play_t *m = w->menus[MAIN];
    // pause
}

void do_cycle_back(main_play_t *m)
{
    m->war->graph->current_cycle--;
    if (m->war->graph->current_cycle < 0)
        m->war->graph->current_cycle = 0;
}

void cycle_back(void *win)
{
    window_t *w = win;
    main_play_t *m = w->menus[MAIN];

    // pause it is not paused
    // pause(m);
    do_cycle_back(m);
}

void do_cycle_front(main_play_t *m)
{
    m->war->graph->current_cycle++;
    if (m->war->graph->current_cycle >= m->war->graph->nbr_cycle_max)
        m->war->graph->current_cycle = m->war->graph->nbr_cycle_max - 1;
}

void cycle_front(void *win)
{
    window_t *w = win;
    main_play_t *m = w->menus[MAIN];

    // pause it is not paused
    // pause(m);
    do_cycle_front(m);
}

main_play_t *create_main_play(sfVector2f size, corewar_grap_t *graph, char **names)
{
    main_play_t *m = malloc(sizeof(main_play_t));
    char *tmp;
    char *save;

    m->rtex = sfRenderTexture_create(size.x, size.y, 0);
    m->war = create_graphic_war((sfVector2f){size.x * 0.5, size.y}, graph);
    my_memset(m->champ_names, 0, sizeof(sfText *) * 5);
    for (int i = 0; names[i]; i++) {
        tmp = my_strdup(names[i]);
        save = tmp;
        while (strchr(tmp, '/'))
            tmp = strchr(tmp, '/') + 1;
        if (index_of('.', tmp) >= 0)
            tmp[index_of('.', tmp)] = 0;
        m->champ_names[i] = init_text(tmp, size.y * 0.15 * 0.4);
        free(save);
        center_text(m->champ_names[i]);
        sfText_setPosition(m->champ_names[i], (sfVector2f){size.x * 0.65 + size.x * 0.15, size.y * 0.03 + size.y * 0.22 * i + size.y * 0.075});
    }
    m->box = init_sprite_from_texture(get_texture_by_name("assets/box.png"));
    set_sprite_size(m->box, (sfVector2f){size.x * 0.3, size.y * 0.15});

    sfVector2f size_fac[3] = {
        {0.1, 0.1}, {0.15, 0.1}, {0.1, 0.1}
    };
    sfVector2f pos_fac[3] = {
        {0.65, 0.9}, {0.8, 0.9}, {0.95, 0.9}
    };
    char *texts[3] = {"<<", "Pause", ">>"};
    void (*actions[3])(void *) = {cycle_back, pause_cycle, cycle_front};

    for (int i = 0; i < 3; i++)
        m->buttons[i] = build_button("sf,pf,ff,base_size,release,text,texture,rect", size_fac[i], pos_fac[i], 0.6, size, actions[i], texts[i], global_texture(), button_rect);
    m->is_paused = 0;
    m->current_cycle = 0;
    return m;
}