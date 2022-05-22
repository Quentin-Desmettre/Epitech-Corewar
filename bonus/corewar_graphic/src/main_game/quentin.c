/*
** EPITECH PROJECT, 2021
** corewar_graphic
** File description:
** quentin.c
*/

#include "rpg.h"

#define CYCLE_PER_SEC 1000

void update_cycles(main_play_t *m)
{
    char *tmp = "Current cycle: ";
    char *tmp2 = nbr_to_str(m->war->graph->current_cycle);
    append(&tmp, tmp2, 0);
    sfText_setString(m->cycle, tmp);
    free(tmp);
    free(tmp2);
    tmp = "Cycle to die: ";
    tmp2 = nbr_to_str(m->war->graph->cycle_to_die[m->war->graph->current_cycle]);
    append(&tmp, tmp2, 0);

    sfText_setString(m->cycle_to_die, tmp);
    free(tmp);
    free(tmp2);
    center_text(m->cycle_to_die);
    center_text(m->cycle);
}

const sfTexture *draw_main_play(window_t *win)
{
    main_play_t *m = win->menus[MAIN];
    sfVector2f size = win_size(win);
    static sfClock *c = NULL;

    if (!c)
        c = sfClock_create();
    if (1 || sfClock_getElapsedTime(c).microseconds > 1000000.0 / CYCLE_PER_SEC) {
        if (m->war->graph->current_cycle < m->war->graph->nbr_cycle_max && !m->is_paused)
            m->war->graph->current_cycle++;
        sfClock_restart(c);
    }
    update_cycles(m);

    sfText_setString(m->buttons[1]->text, m->is_paused ? "Resume" : "Pause");

    sfRenderTexture_clear(m->rtex, sfBlack);

    draw_graph(m->war);
    sfSprite *s = init_sprite_from_texture(sfRenderTexture_getTexture(m->war->rtex));
    sfRenderTexture_drawSprite(m->rtex, s, NULL);
    sfSprite_destroy(s);

    for (int i = 0; m->champ_names[i]; i++) {
        sfSprite_setPosition(m->box, (sfVector2f){size.x * 0.85, size.y * 0.09 + size.y * 0.17 * i});
        sfRenderTexture_drawSprite(m->rtex, m->box, NULL);
        sfText_setFillColor(m->champ_names[i], m->war->graph->is_dead[m->war->graph->current_cycle][i] ? sfRed : sfGreen);
        sfRenderTexture_drawText(m->rtex, m->champ_names[i], NULL);
    }
    for (int i = 0; i < 3; i++)
        draw_button_to_rtex(m->buttons[i], m->rtex);
    if (m->war->graph->current_cycle == m->war->graph->nbr_cycle_max)
        sfRenderTexture_drawText(m->rtex, m->winner, NULL);
    sfRenderTexture_drawText(m->rtex, m->cycle, NULL);
    sfRenderTexture_drawText(m->rtex, m->cycle_to_die, NULL);
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

    m->is_paused = !m->is_paused;
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

    m->is_paused = 1;
    do_cycle_back(m);
}

void do_cycle_front(main_play_t *m)
{
    m->war->graph->current_cycle++;
    if (m->war->graph->current_cycle > m->war->graph->nbr_cycle_max)
        m->war->graph->current_cycle = m->war->graph->nbr_cycle_max;
}

void cycle_front(void *win)
{
    window_t *w = win;
    main_play_t *m = w->menus[MAIN];

    m->is_paused = 1;
    do_cycle_front(m);
}

main_play_t *create_main_play(sfVector2f size, corewar_grap_t *graph, char **names)
{
    main_play_t *m = malloc(sizeof(main_play_t));
    char *tmp;
    char *save;

    m->rtex = sfRenderTexture_create(size.x, size.y, 0);
    m->war = create_graphic_war((sfVector2f){size.x, size.y}, graph);
    my_memset(m->champ_names, 0, sizeof(sfText *) * 5);
    for (int i = 0; names[i]; i++) {
        tmp = my_strdup(names[i]);
        save = tmp;
        while (strchr(tmp, '/'))
            tmp = strchr(tmp, '/') + 1;
        if (index_of('.', tmp) >= 0)
            tmp[index_of('.', tmp)] = 0;
        m->champ_names[i] = init_text(tmp, size.y * 0.12 * 0.4);
        sfText_setFillColor(m->champ_names[i], sfGreen);
        free(save);
        center_text(m->champ_names[i]);
        sfText_setPosition(m->champ_names[i], (sfVector2f){size.x * 0.65 + size.x * 0.15, size.y * 0.03 + size.y * 0.17 * i + size.y * 0.06});
    }
    m->box = init_sprite_from_texture(get_texture_by_name("assets/box.png"));
    set_sprite_size(m->box, (sfVector2f){size.x * 0.27, size.y * 0.12});
    center_sprite(m->box);

    sfVector2f size_fac[3] = {
        {0.07, 0.07}, {0.12, 0.07}, {0.07, 0.07}
    };
    sfVector2f pos_fac[3] = {
        {0.75, 0.915}, {0.85, 0.915}, {0.95, 0.915}
    };
    char *texts[3] = {"<<", "Pause", ">>"};
    void (*actions[3])(void *) = {cycle_back, pause_cycle, cycle_front};

    for (int i = 0; i < 3; i++)
        m->buttons[i] = build_button("sf,pf,ff,base_size,release,text,texture,rect", size_fac[i], pos_fac[i], 0.6, size, actions[i], texts[i], global_texture(), button_rect);
    m->is_paused = 0;
    m->current_cycle = 0;
    m->is_paused = 0;
    m->winner = init_text(m->war->graph->winner_str, size.x / my_strlen(m->war->graph->winner_str));
    center_text(m->winner);
    sfText_setPosition(m->winner, (sfVector2f){size.x * 0.5, size.y * 0.5});

    m->cycle_to_die = init_text("0", size.y * 0.031);
    m->cycle = init_text("0", size.y * 0.031);
    center_text(m->cycle_to_die);
    center_text(m->cycle);
    sfText_setPosition(m->cycle, (sfVector2f){size.x * 0.85, size.y * 0.72});
    sfText_setPosition(m->cycle_to_die, (sfVector2f){size.x * 0.85, size.y * 0.8});
    sfText_setOutlineColor(m->cycle, sfBlack);
    sfText_setOutlineThickness(m->cycle, size.y * 0.027 * 0.2);
    sfText_setOutlineColor(m->cycle_to_die, sfBlack);
    sfText_setOutlineThickness(m->cycle_to_die, size.y * 0.027 * 0.2);
    return m;
}