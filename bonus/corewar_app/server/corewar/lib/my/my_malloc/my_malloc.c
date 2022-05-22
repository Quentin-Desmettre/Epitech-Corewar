/*
** EPITECH PROJECT, 2021
** lib
** File description:
** my_malloc.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "linked_list.h"

void my_exit(int code);

static s_list_t **malloc_stack(void)
{
    static s_list_t *n = 0;

    return &n;
}

void flush_garbage(void)
{
    s_list_t *next;
    s_list_t *head = *(malloc_stack());

    while (head) {
        free(head->data);
        next = head->next;
        free(head);
        head = next;
    }
    *(malloc_stack()) = NULL;
}

void my_free(void *data)
{
    s_list_t *prev = NULL;
    s_list_t *head = *(malloc_stack());

    free(data);
    while (head) {
        if (head->data == data) {
            prev ?
            (prev->next = head->next) :
            (*(malloc_stack()) = head->next);
            free(head);
            return;
        }
        prev = head;
        head = head->next;
    }
}

void push_to_stack(s_list_t **stack, void *data)
{
    s_list_t *node = malloc(sizeof(s_list_t));

    if (!node) {
        write(2, "ERROR: malloc() failed.\n", 24);
        my_exit(84);
    }
    node->data = data;
    node->next = *stack;
    *stack = node;
}

void *my_malloc(size_t size)
{
    void *r = malloc(size);

    if (!r) {
        write(2, "ERROR: malloc() failed.\n", 24);
        my_exit(84);
    }
    push_to_stack(malloc_stack(), r);
    return r;
}
