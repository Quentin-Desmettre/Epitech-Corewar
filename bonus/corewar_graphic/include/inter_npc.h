/*
** EPITECH PROJECT, 2022
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** inter_npc
*/

#ifndef INTER_NPC_H_
    #define INTER_NPC_H_

    #define PNJ_SPRITE "assets/pnj.png"
    #define PNJ_TALK_BOX "assets/pnj_box.png"
    #define TALK 0
    #define QUEST 1
    #define OPT_DIALOG "assets/pnj_opt_box.png"
    #define ARROW_PNG "assets/arrow.png"
    #define NB_TEXTS 5

    #include "rpg.h"

sfTexture *get_texture_by_name(char const *name);
list_t **textures_list(void);
void destroy_texture(void *tex);

#endif /* !INTER_NPC_H_ */
