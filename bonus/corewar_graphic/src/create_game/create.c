/*
** EPITECH PROJECT, 2021
** corewar_graphic
** File description:
** create.c
*/

#include "rpg.h"
#include "op.h"

typedef struct {
    sfText *name;
    sfSprite *box;
} gui_champ_t;

gui_champ_t *create_gui_champ(char const *path, sfVector2f size, sfVector2f pos)
{
    gui_champ_t *g = malloc(sizeof(gui_champ_t));
    char *p = my_strdup(path);

    if (index_of('.', p) > 0)
        p[index_of('.', p)] = 0;
    g->name = init_text(p, size.y * 0.6);
    g->box = init_sprite_from_texture(get_texture_by_name("assets/box.png"));
    set_sprite_size(g->box, size);
    sfSprite_setPosition(g->box, pos);
    center_text(g->name);
    sfText_setPosition(g->name, (sfVector2f){pos.x + size.x * 0.5, pos.y + size.y * 0.5});
    return g;
}

void move_champs(champ_select_t *c, float dir)
{
    list_t *begin = c->champs;
    gui_champ_t *gui;

    if (!begin)
        return;
    do {
        gui = begin->data;
        sfSprite_move(gui->box, (sfVector2f){0, dir});
        sfText_move(gui->name, (sfVector2f){0, dir});
        begin = begin->next;
    } while (begin != c->champs);
}

void create_champ_entries(champ_select_t *c, sfVector2f size)
{
    system("find champions -name \"*.cor\" > /tmp/champions");
    FILE *f = fopen("/tmp/champions", "r");
    char *buf = NULL;
    char *new;
    size_t tmp;
    gui_champ_t *gui;
    int nb_created = 0;
    c->all_files = malloc(sizeof(char *));

    c->all_files[0] = NULL;

    if (!f)
        return;
    while (getline(&buf, &tmp, f) > 0) {
        append_str_array(&c->all_files, buf);
        new = buf;
        while (strchr(new, '/'))
            new = strchr(new, '/') + 1;
        gui = create_gui_champ(new, (sfVector2f){size.x * 0.7, size.y * 0.2}, (sfVector2f){size.x * 0.15, size.y * (0.1 + nb_created * 0.3)});
        append_node(&c->champs, gui);
        buf = NULL;
        nb_created++;
    }
    c->is_selected = malloc(sizeof(int) * nb_created);
    for (int i = 0; i < nb_created; i++)
        c->is_selected[i] = 0;
    fclose(f);
}

champ_select_t *create_champ_select(sfVector2f size)
{
    champ_select_t *c = malloc(sizeof(champ_select_t));

    c->rtex = sfRenderTexture_create(size.x, size.y, 0);
    c->champs = NULL;
    c->nb_selected = 0;
    create_champ_entries(c, size);
    c->box = init_sprite_from_texture(get_texture_by_name("assets/bigbox.png"));
    set_sprite_size(c->box, size);
    c->select = create_rectangle((sfVector2f){size.x * 0.7, size.y * 0.2}, sfTransparent, size.x * 0.01, (sfColor){180, 0, 0, 255});
    return c;
}

void draw_champ_select(champ_select_t *c, sfRenderTexture *rtex, sfVector2f pos)
{
    int current = 0;
    list_t *begin = c->champs;
    gui_champ_t *gui;

    sfRenderTexture_clear(c->rtex, sfTransparent);
    if (begin) {
        do {
            gui = begin->data;
            sfRenderTexture_drawSprite(c->rtex, gui->box, NULL);
            sfRenderTexture_drawText(c->rtex, gui->name, NULL);
            if (c->is_selected[current]) {
                sfRectangleShape_setPosition(c->select, sfSprite_getPosition(gui->box));
                sfRenderTexture_drawRectangleShape(c->rtex, c->select, NULL);
            }
            begin = begin->next;
            current++;
        } while (begin != c->champs);
    }
    sfRenderTexture_drawSprite(c->rtex, c->box, NULL);
    sfRenderTexture_display(c->rtex);
    sfSprite *new = init_sprite_from_texture(sfRenderTexture_getTexture(c->rtex));
    sfSprite_setPosition(new, pos);
    sfRenderTexture_drawSprite(rtex, new, NULL);
    sfSprite_destroy(new);
}

void go_to_home(void *win)
{
    set_next_win_state(win, HOME);
}

const sfTexture *draw_play(window_t *win)
{
    play_t *p = win->menus[PLAY];
    sfVector2u size = sfRenderTexture_getSize(p->rtex);

    sfRenderTexture_clear(p->rtex, grey);
    sfRenderTexture_drawText(p->rtex, p->choose, NULL);
    sfRenderTexture_drawSprite(p->rtex, p->logo, NULL);
    for (int i = 0; i < 2; i++)
        draw_button_to_rtex(p->buttons[i], p->rtex);
    draw_champ_select(p->select, p->rtex, (sfVector2f){size.x * 0.06, size.y * 0.3});
    sfRenderTexture_display(p->rtex);
    return sfRenderTexture_getTexture(p->rtex);
}

void destroy_entry(void *gui)
{
    gui_champ_t *g = gui;
    sfSprite_destroy(g->box);
    sfText_destroy(g->name);
    free(g);
}

void destroy_select(champ_select_t *c)
{
    sfRenderTexture_destroy(c->rtex);
    sfSprite_destroy(c->box);
    sfRectangleShape_destroy(c->select);

    while (c->champs)
        remove_node(&c->champs, 0, destroy_entry);
    free(c->is_selected);
    free_str_array(c->all_files, 0);
    free(c);
}

void destroy_create_play(play_t *p)
{
    sfRenderTexture_destroy(p->rtex);
    destroy_button(p->buttons[0]);
    destroy_button(p->buttons[1]);
    sfText_destroy(p->choose);
    sfSprite_destroy(p->logo);
    destroy_select(p->select);
    free(p);
}

void check_entries(play_t *p, sfVector2f pos)
{
    sfVector2u size = sfRenderTexture_getSize(p->rtex);
    champ_select_t *c = p->select;
    sfFloatRect bounds;
    list_t *begin = c->champs;
    gui_champ_t *gui;
    int current = 0;

    if (begin) {
        do {
            gui = begin->data;
            bounds = sfSprite_getGlobalBounds(gui->box);
            bounds.left += size.x * 0.06;
            bounds.top += size.y * 0.3;
            if (sfFloatRect_contains(&bounds, pos.x, pos.y)) {
                if (c->is_selected[current]) {
                    c->is_selected[current] = 0;
                    c->nb_selected--;
                } else if (c->nb_selected < 4) {
                    c->is_selected[current] = 1;
                    c->nb_selected++;
                }
            }
            begin = begin->next;
            current++;
        } while (begin != c->champs);
    }
    if (c->nb_selected > 1)
        set_button_enabled(p->buttons[1], 1);
    else
        set_button_enabled(p->buttons[1], 0);
}

void play_events(window_t *win, sfEvent ev)
{
    play_t *p = win->menus[PLAY];
    sfVector2u size = sfRenderTexture_getSize(p->rtex);

    if (ev.type == sfEvtMouseMoved)
        check_button_move(p->buttons, 2, ev.mouseMove.x, ev.mouseMove.y);
    if (ev.type == sfEvtMouseButtonPressed)
        check_button_press(p->buttons, 2, ev.mouseButton.x, ev.mouseButton.y);
    if (ev.type == sfEvtMouseButtonReleased) {
        check_button_release(p->buttons, 2, (sfVector2f){ev.mouseButton.x, ev.mouseButton.y}, win);
        check_entries(p, (sfVector2f){ev.mouseButton.x, ev.mouseButton.y});
    }
    if (ev.type == sfEvtMouseWheelScrolled)
        move_champs(p->select, ev.mouseWheelScroll.delta * size.y * 0.01);
}

char **get_selected_champions(play_t *p)
{
    char **selected = malloc(sizeof(char *) * (p->select->nb_selected + 2));
    int nb = 0;

    selected[0] = my_strdup("./corewar");
    nb = 1;
    for (int i = 0; p->select->all_files[i] && nb < p->select->nb_selected + 1; i++) {
        if (p->select->is_selected[i]) {
            selected[nb] = my_strdup(p->select->all_files[i]);
            if (index_of('\n', selected[nb]) >= 0)
                selected[nb][index_of('\n', selected[nb])] = 0;
            nb++;
        }
    }
    selected[p->select->nb_selected + 1] = 0;
    return selected;
}

void go_to_real_play(void *win)
{
    window_t *w = win;
    corewar_grap_t *graph = NULL;
    char **av = get_selected_champions(w->menus[PLAY]);

    graph = setup_game(my_str_array_len(av), av);
    set_next_win_state(win, MAIN);
    w->menus[MAIN] = create_main_play(win_size(w), graph, av + 1);
    free_str_array(av, 1);
}

play_t *create_play(sfVector2f size)
{
    play_t *p = malloc(sizeof(play_t));
    sfVector2f pf[2] = {
        {0.65, 0.92}, {0.87, 0.92}
    };
    sfVector2f sf[2] = {
        {0.2, 0.1}, {0.2, 0.1}
    };
    char *txt[2] = {"Cancel", "Play"};
    void (*action[2])(void *) = {go_to_home, go_to_real_play};

    p->rtex = sfRenderTexture_create(size.x, size.y, 0);
    p->logo = init_sprite_from_texture(get_texture_by_name("assets/corewar.png"));
    set_sprite_size(p->logo, (sfVector2f){size.x * 0.3, size.x * 0.3 / 1.27848101266});
    center_sprite(p->logo);
    sfSprite_setPosition(p->logo, (sfVector2f){size.x * 0.8, size.x * 0.3 / 1.27848101266});
    p->choose = init_text("Choose your champions.", size.y * 0.1);
    sfText_setPosition(p->choose, (sfVector2f){size.x * 0.05, size.y * 0.05});
    p->select = create_champ_select((sfVector2f){size.x * 0.4, size.y * 0.6});
    for (int i = 0; i < 2; i++) {
        p->buttons[i] = build_button("sf,pf,ff,base_size,release,text,texture,rect,p_sf,r_sf", sf[i], pf[i], 0.6, size, action[i], txt[i], global_texture(), button_rect, BUTTON_PRESS, BUTTON_RELEASE);
    }
    set_button_enabled(p->buttons[1], 0);
    return p;
}
