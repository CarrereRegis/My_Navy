/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** game_loop header
*/

#include <malloc.h>

#include "../include/game_loop.h"
#include "connection_handler_extra.h"
#include "destroyer.h"
#include "my.h"
#include "my_printf.h"
#include "player_io.h"
#include "render.h"

static
int execute_when_local(game_t *game)
{
    vector_2i_t *pos = NULL;
    bool hit;

    pos = wait_for_input(game);
    if (pos == NULL)
        return -1;
    send_pos(game->con, pos);
    hit = wait_for_hit(game->con);
    my_printf("%c%d: %s\n", pos->x + 'A', pos->y + 1,
        hit ? "hit" : "missed");
    game->remote_map[pos->y][pos->x] = (char) (hit ? 'x' : 'o');
    free(pos);
    return 0;
}

static
int execute_when_remote(game_t *game)
{
    vector_2i_t *target_pos = NULL;
    bool hit;

    my_printf("waiting for enemy's attack...\n");
    target_pos = wait_for_pos(game->con);
    if (target_pos == NULL)
        return -1;
    hit = game->map[target_pos->y][target_pos->x] != '.';
    send_hit(game->con, hit);
    my_printf("%c%d: %s\n", target_pos->x + 'A', target_pos->y + 1,
        hit ? "hit" : "missed");
    if (hit)
        game->map[target_pos->y][target_pos->x] = 'x';
    if (!hit && game->map[target_pos->y][target_pos->x] != 'x')
        game->map[target_pos->y][target_pos->x] = 'o';
    free(target_pos);
    return 0;
}

static
bool are_all_boat_on_row_sinked(game_t *game, int y)
{
    for (int x = 0; x < MAP_SIZE; x += 1) {
        if (IS_NUM(game->map[y][x])) {
            return false;
        }
    }
    return true;
}

static
bool are_all_boats_sinked(game_t *game)
{
    for (int y = 0; y < MAP_SIZE; y += 1) {
        if (are_all_boat_on_row_sinked(game, y) == false) {
            return false;
        }
    }
    return true;
}

static
int tick_game(game_t *game)
{
    if (game->current_turn == LOCAL) {
        if (execute_when_local(game) == -1)
            return -1;
        if (are_all_boats_sinked(game))
            return 1;
        return execute_when_remote(game);
    }
    if (execute_when_remote(game) == -1)
        return -1;
    if (are_all_boats_sinked(game))
        return 1;
    return execute_when_local(game);
}

int game_loop(game_t *game)
{
    while (game->playing) {
        render_game(game);
        if (tick_game(game) != 0) {
            game->playing = false;
        }
    }
    destroy_game_content(game);
    return 0;
}
