/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** render header
*/

#include "render.h"
#include "../include/my_printf.h"

static
void print_map_cell(char chr, int x)
{
    if (x == 0) {
        my_printf("%c", chr);
    } else {
        my_printf(" %c", chr);
    }
}

void render_game(game_t *game)
{
    my_printf("my positions:\n");
    render_map(game->map);
    my_printf("enemy's positions:\n");
    render_map(game->remote_map);
}

void render_map(char map[MAP_SIZE][MAP_SIZE])
{
    my_printf("%s\n", " |A B C D E F G H");
    my_printf("%s\n", "-+---------------");
    for (int y = 0; y < MAP_SIZE; y += 1) {
        my_printf("%d|", y + 1);
        for (int x = 0; x < MAP_SIZE; x += 1) {
            print_map_cell(map[y][x], x);
        }
        my_printf("\n");
    }
}
