/*
** EPITECH PROJECT, 2021
** corewar_graphic
** File description:
** create.c
*/

#include "rpg.h"
#include "op.h"

void quit_main_menuu(void *win)
{
    set_next_win_state(win, EXIT);
}

void go_to_settingss(void *win)
{
    set_next_win_state(win, SETTINGS);
}

void go_to_play(void *win)
{
    // play
    set_next_win_state(win, PLAY);
}

void main_menu_events(window_t *win, sfEvent ev)
{
    main_menu_tt *m = win->menus[HOME];

    if (ev.type == sfEvtMouseMoved)
        check_button_move(m->buttons, 3, ev.mouseMove.x, ev.mouseMove.y);
    if (ev.type == sfEvtMouseButtonPressed)
        check_button_press(m->buttons, 3, ev.mouseButton.x, ev.mouseButton.y);
    if (ev.type == sfEvtMouseButtonReleased)
        check_button_release(m->buttons, 3, (sfVector2f){ev.mouseButton.x, ev.mouseButton.y}, win);
}

sfTexture const *draw_main_menuu(window_t *win)
{
    main_menu_tt *m = win->menus[HOME];

    sfRenderTexture_clear(m->rtex, sfBlack);
    sfRenderTexture_drawSprite(m->rtex, m->corewar, NULL);
    sfRenderTexture_drawSprite(m->rtex, m->logo, NULL);
    for (int i = 0; i < 3; i++)
        draw_button_to_rtex(m->buttons[i], m->rtex);
    sfRenderTexture_display(m->rtex);
    return sfRenderTexture_getTexture(m->rtex);
}

void rescale_main_menuu(main_menu_tt *m, sfVector2f size)
{
    sfRenderTexture_destroy(m->rtex);
    m->rtex = sfRenderTexture_create(size.x, size.y, 0);

    set_sprite_size(m->corewar, size);
    center_sprite(m->logo);
    set_sprite_size(m->logo, (sfVector2f){size.x * 0.3, size.x * 0.3 / 1.27848101266});
    sfSprite_setPosition(m->logo, (sfVector2f){size.x * 0.5, size.x * 0.13});
    for (int i = 0; i < 3; i++) {
        m->buttons[i]->container_size = size;
        update_button(m->buttons[i]);
    }
}

main_menu_tt *create_main_menuu(sfVector2f size)
{
    main_menu_tt *m = malloc(sizeof(main_menu_tt));
    sfVector2f size_factors[3] = {
        {0.13, 0.08}, {0.3, 0.12}, {0.3, 0.12}
    };
    sfVector2f pos_factors[3] = {
        {0.08, 0.05}, {0.3, 0.85}, {0.7, 0.85}
    };
    void (*actions[3])(void *) = {quit_main_menuu, go_to_settingss, go_to_play};
    char *texts[3] = {"Quit", "Settings", "Play"};

    m->logo = init_sprite_from_texture(get_texture_by_name("assets/corewar.png"));
    center_sprite(m->logo);
    set_sprite_size(m->logo, (sfVector2f){size.x * 0.3, size.y * 0.3});
    sfSprite_setPosition(m->logo, (sfVector2f){size.x * 0.5, size.x * 0.13});
    m->corewar = init_sprite_from_texture(get_texture_by_name("assets/logo.png"));
    set_sprite_size(m->corewar, size);
    for (int i = 0; i < 3; i++) {
        m->buttons[i] = build_button("sf,pf,ff,base_size,release,text,texture,p_sf,r_sf,rect",
        size_factors[i], pos_factors[i], i ? 0.6 : 0.8, size, actions[i], texts[i], global_texture(), BUTTON_PRESS, BUTTON_RELEASE, button_rect);
    }
    m->rtex = sfRenderTexture_create(size.x, size.y, 0);
    return m;
}