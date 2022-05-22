/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** init_window.c
*/

#include "rpg.h"

void play_events(window_t *win, sfEvent ev);

static void create_basics(window_t *win)
{
    win->state = HOME;
    win->next_state = HOME;
    win->is_transition = 0;
    win->mode = (sfVideoMode){800, 600, 32};
    win->lum_clock = create_clock();
    win->music = create_music(LOBBY_MUSIC);
    if (win->music) {
        sfMusic_play(win->music);
        sfMusic_setVolume(win->music, 30);
        sfMusic_setLoop(win->music, 1);
    }
}

static void create_settings(window_t *win)
{
    win->menus[SETTINGS] = init_settings(win);
    load_settings(win->menus[SETTINGS]);
}

static void create_pointers(window_t *win)
{
    const sfTexture* (*dr[])(window_t *) = {
        draw_settings, draw_main_menuu, NULL, draw_play, draw_main_play
    };
    void (*ev[])(window_t *, sfEvent) = {
        settings_ev, main_menu_events, NULL, play_events, main_play_ev
    };

    for (int i = 0; i < 5; i++) {
        win->draw[i] = dr[i];
        win->event[i] = ev[i];
    }
}

window_t *window_create(void)
{
    window_t *win = malloc(sizeof(window_t));

    memset(win->menus, 0, sizeof(void *) * 12);
    create_pointers(win);
    create_basics(win);
    create_settings(win);
    win->menus[HOME] = create_main_menuu(win_size(win));
    apply_settings(win->menus[SETTINGS], win);
    win->menus[PLAY] = create_play(win_size(win));
    return win;
}
