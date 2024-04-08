/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** player_io header
*/

#include <malloc.h>

#include "../include/player_io.h"
#include "../include/my.h"
#include "../include/my_parser.h"
#include "my_printf.h"

static
char *get_from_stdin(void)
{
    char *line = NULL;
    size_t buff_value = 0;
    int rt_value;

    rt_value = (int) getline(&line, &buff_value, stdin);
    if (rt_value <= 0) {
        free(line);
        return NULL;
    }
    return line;
}

static
bool is_pos_valid(char *input, game_t *game)
{
    if (input == NULL)
        return false;
    if (my_strlen(input) != 3)
        return false;
    if (!(CHAR_A_TO_H(input[0]) && IS_NUM(input[1])))
        return false;
    if ((input[1] - '0') > MAP_SIZE || (input[1] - '0') == 0)
        return false;
    if (game->remote_map[input[1] - '1'][input[0] - 'A'] != '.')
        return false;
    return true;
}

static
int manage_input(char **input, bool *first_try)
{
    if (!(*first_try))
        my_printf("wrong position\n");
    if ((*input) != NULL)
        free(*input);
    my_printf("attack: ");
    *input = get_from_stdin();
    if (*input == NULL)
        return -1;
    (*first_try) = false;
    return 0;
}

vector_2i_t *wait_for_input(game_t *game)
{
    vector_2i_t *new = malloc(sizeof(vector_2i_t));
    char *input = NULL;
    bool first_try = true;

    if (new == NULL)
        return NULL;
    while (!is_pos_valid(input, game)) {
        if (manage_input(&input, &first_try) != 0) {
            free(new);
            return NULL;
        }
    }
    new->x = input[0] - 'A';
    new->y = input[1] - '1';
    free(input);
    return new;
}
