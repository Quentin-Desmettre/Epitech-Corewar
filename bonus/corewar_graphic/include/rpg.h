/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** rpg.h
*/

#ifndef RPG_H
    #define RPG_H
    #include <string.h>
    #include <SFML/Window.h>
    #include <SFML/Graphics.h>
    #include "my_clock.h"
    #include "settings.h"
    #include "sprite.h"
    #include "inter_npc.h"
    #include "audio_builder.h"
    #include <math.h>
    #include "op.h"

    #define ABS(x) ((x) < 0 ? -(x) : (x))
    #define REPEAT_DELAY 500000
    #define SPACING 0.06
    #define BUTTON_PRESS "assets/audio/button_press.ogg"
    #define BUTTON_RELEASE "assets/audio/button_release.ogg"
    #define LOBBY_MUSIC "assets/audio/lobby.ogg"

typedef struct {
    sfSprite *logo;
    sfSprite *corewar;
    button_t *buttons[3];
    sfRenderTexture *rtex;
} main_menu_tt;

typedef struct {
    sfRenderTexture *rtex;
    sfSprite *box;
    sfRectangleShape *select;
    list_t *champs;
    int *is_selected;
    int nb_selected;
    char **all_files;
} champ_select_t;

typedef struct {
    sfSprite *logo;
    sfText *choose;
    button_t *buttons[2];
    sfRenderTexture *rtex;
    champ_select_t *select;
} play_t;

typedef struct win {
    sfVideoMode mode;
    sfRenderWindow *win;
    int state;
    void *menus[12];
    p_clock_t *lum_clock;

    int is_transition;
    int next_state;
    int framerate;

    const sfTexture* (*draw[12])(struct win *);
    void (*event[12])(struct win *, sfEvent ev);
    void (*update[12])(void *);

    sfMusic *music;
    sfSound *close_sfx;
} window_t;

typedef struct {
    sfRenderTexture *rtex;
    corewar_grap_t *graph;
    sfView *view;
    sfText *byte;
    sfRectangleShape *rect;
    sfVector2i oldMousePos;
    float zoom;
} graphic_war_t;

typedef struct {
    graphic_war_t *war;
    sfRenderTexture *rtex;
    button_t *buttons[3]; // cycle++, cycle--, play/pause
    // cycle++, cycle-- mettent automatiquement en pause
    sfSprite *box;
    sfText *champ_names[5];
    sfSprite *corewar;
    int is_paused;
    int current_cycle;
    sfText *winner;
    sfText *cycle_to_die;
    sfText *cycle;
} main_play_t;

typedef enum {
    SETTINGS, HOME, EXIT, PLAY, MAIN
} state_t;

static const sfIntRect back_rect = {
    0, 0, 1, 1
};

static const sfColor grey = {
    128, 128, 128, 255
};

static const sfIntRect stats_rects[] = {
    {648, 671, 125, 124}, // strength
    {775, 671, 128, 117}, // speed
    {648, 799, 128, 128}, // defense
    {776, 799, 128, 128} // thirst
};

static const sfIntRect icon_rect = {
    0, 671, 648, 648
};

static const sfIntRect hider_rect = {
    82, 241, 128, 128
};
static const sfIntRect button_rect = {0, 81, 315, 80};

typedef struct {
    sfRenderTexture *rtex;
    sfRectangleShape *background;
    p_clock_t *underscore;
    sfText *text;
    int has_underscore;
    int max_char;
} line_edit_t;

sfSprite *get_settings_sprite(window_t *win);
void move_settings(settings_t *se, window_t *win);
void go_back(settings_t *se, window_t *win);
void update_full_screen(settings_t *se, window_t *win);
void update_vsync(settings_t *se, window_t *win);
void update_res(settings_t *se, window_t *win);
void update_framerate(settings_t *se, window_t *win);
void rescale_settings(settings_t *se, window_t *win);
sfFloatRect bounds(sfSprite *s);
sfVector2f conv(sfVector2f c, window_t *win);
int get_set_button_at(settings_t *se, sfEvent *ev);
void manage_settings_hover(sfEvent *ev, window_t *win);
void manage_settings_press(sfEvent *ev, window_t *win);
void manage_settings_release(sfEvent *ev, window_t *win);
void reset_set_buttons(settings_t *se);
void update_all_texts(settings_t *se);
void sfx_minus(settings_t *se);
void sfx_plus(settings_t *se);
void music_minus(settings_t *se);
void music_plus(settings_t *se);
void update_vol(float m_vol, float s_vol, char const *format, ...);
void settings_ev(window_t *win, sfEvent ev);
const sfTexture *draw_settings(window_t *win);
settings_t *init_settings(window_t *win);
void check_sound_repeat(window_t *win, sfEvent *ev);
void main_menu_events(window_t *win, sfEvent ev);
sfTexture const *draw_main_menuu(window_t *win);
main_menu_tt *create_main_menuu(sfVector2f size);
sfVector2f win_size(window_t *win);
void rescale_all(window_t *win);
void set_next_win_state(window_t *win, int next);
void remove_last_text(sfText *t);
void append_to_text(sfText *t, char c);
void save_settings(settings_t *se);
void update_transition(window_t *win, sfSprite *s);
window_t *window_create(void);
window_t *window(window_t *ptr);
void free_textures(void);
void apply_settings(settings_t *se, window_t *win);
play_t *create_play(sfVector2f size);
const sfTexture *draw_play(window_t *win);
void draw_graph(graphic_war_t *g);
void graph_ev(graphic_war_t *g, sfEvent ev);
graphic_war_t *create_graphic_war(sfVector2f size, corewar_grap_t *graph);
void main_play_ev(window_t *win, sfEvent ev);
main_play_t *create_main_play(sfVector2f size, corewar_grap_t *graph, char **champs);
const sfTexture *draw_main_play(window_t *win);

#endif
