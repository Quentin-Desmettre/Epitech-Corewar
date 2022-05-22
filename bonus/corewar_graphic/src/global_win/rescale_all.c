/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myworld-paulin.leclercq
** File description:
** rescale_all.c
*/

#include "rpg.h"

void rescale_main_menuu(main_menu_tt *m, sfVector2f size);

void rescale_all(window_t *win)
{
    rescale_settings(win->menus[SETTINGS], win);
    rescale_main_menuu(win->menus[HOME], win_size(win));
}
