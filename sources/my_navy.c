/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** my_navy header
*/

#include <stdlib.h>
#include <unistd.h>

#include "../include/connection_handler.h"
#include "../include/my.h"
#include "../include/my_navy.h"
#include "../include/my_printf.h"
#include "game_loop.h"
#include "my_parser.h"

static
void fill_map(game_t *game)
{
    for (int y = 0; y < MAP_SIZE; y += 1) {
        for (int x = 0; x < MAP_SIZE; x += 1) {
            game->map[y][x] = '.';
            game->remote_map[y][x] = '.';
        }
    }
}

static
void load_params_in_game(game_t *game, char **argv)
{
    if (game->mode == SERVER) {
        game->map_script_path = my_strdup(argv[1]);
    } else {
        game->map_script_path = my_strdup(argv[2]);
    }
}

static
int launch_game(game_t *game, char **argv)
{
    int my_pid = getpid();

    load_params_in_game(game, argv);
    fill_map(game);
    if (parse_file(game) != 0)
        return EXIT_FAILURE_TECH;
    my_printf("my_pid: %d\n", my_pid);
    if (game->mode == SERVER) {
        game->con = wait_for_connection();
    } else {
        if (argv[1] == NULL || my_getnbr(argv[1]) == 0)
            return EXIT_FAILURE_TECH;
        game->con = init_connection(my_getnbr(argv[1]));
    }
    if (game->con == NULL)
        return EXIT_FAILURE_TECH;
    return game_loop(game);
}

static
int print_helper(void)
{
    my_printf(""
        "USAGE\n"
        "\t./my_navy [first_player_pid] navy_positions\n"
        "DESCRIPTION:\n"
        "\tfirst_player_pid: only for the 2nd player. "
        "pid of the first player.\n"
        "\tnavy_positions: file representing the positions of the ships.\n");
    return EXIT_SUCCESS;
}

int my_navy(int argc, char **argv)
{
    game_t game = {0};

    if (argc == 2 && my_strcmp(argv[1], "-h") == 0)
        return print_helper();
    if (argc == 2)
        game.mode = SERVER;
    if (argc == 3)
        game.mode = CLIENT;
    if (game.mode == UNKNOWN || argv[1] == NULL)
        return EXIT_FAILURE_TECH;
    game.playing = true;
    game.current_turn = (game.mode == SERVER) ? LOCAL : REMOTE;
    return launch_game(&game, argv);
}
