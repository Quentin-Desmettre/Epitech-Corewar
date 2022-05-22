/*
** EPITECH PROJECT, 2021
** B-MUL-200-LIL-2-1-myrpg-quentin.desmettre
** File description:
** rotate_vector.c
*/

#include <SFML/Graphics.h>
#include "rpg.h"
#define PI 3.141
static inline float deg_to_rad(float degree)
{
    return degree * PI / 180.0;
}

void rotate_vector(sfVector2f *vec, float degree)
{
    sfVector2f new;

    degree = deg_to_rad(degree);
    new.x = cos(degree) * vec->x - sin(degree) * vec->y;
    new.y = sin(degree) * vec->x + cos(degree) * vec->y;
    vec->x = new.x;
    vec->y = new.y;
}

sfVector2i sprite_pos(sfSprite *s)
{
    sfVector2f pos = sfSprite_getPosition(s);

    return (sfVector2i){pos.x, pos.y};
}
