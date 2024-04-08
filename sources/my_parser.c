/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** my_parser header
*/

#include <stddef.h>
#include <stdio.h>
#include <malloc.h>

#include "../include/my_parser.h"
#include "../include/my.h"

static
int load_boat(game_t *game, boat_t *boat)
{
    if (boat->start->x == boat->end->x) {
        for (int i = 0; i <= ABS(boat->start->y - boat->end->y); i += 1) {
            game->map[MIN(boat->start->y, boat->end->y) + i][boat->start->x] =
                (char) ('0' + boat->len);
        }
        return 0;
    }
    if (boat->start->y == boat->end->y) {
        for (int i = 0; i <= ABS(boat->start->x - boat->end->x); i += 1) {
            game->map[boat->start->y][MIN(boat->start->x, boat->end->x) + i] =
                (char) ('0' + boat->len);
        }
        return 0;
    }
    return -1;
}

static
bool is_delta_valid(char const *line, int given_len)
{
    int x_a = line[2] - 'A';
    int y_a = line[3] - '0';
    int x_b = line[5] - 'A';
    int y_b = line[6] - '0';
    int delta_pos = ABS(x_a - x_b + y_a - y_b) + 1;

    return (delta_pos == given_len);
}

static
bool is_line_valid(char *line)
{
    if (line == NULL || my_strlen(line) != (NORMAL_LINE_LEN + 1))
        return false;
    if (!(line[1] == ':' && line[4] == ':'))
        return false;
    if (!(IS_NUM(line[0]) && IS_NUM(line[3]) && IS_NUM(line[6])))
        return false;
    if (!(CHAR_A_TO_H(line[2]) && CHAR_A_TO_H(line[5])))
        return false;
    return is_delta_valid(line, (line[0] - '0'));
}

static
int analyze_line(game_t *game, char *line)
{
    vector_2i_t start = {0};
    vector_2i_t end = {0};
    boat_t boat = {0};

    if (line == NULL || !is_line_valid(line))
        return -1;
    start.x = line[2] - 'A';
    start.y = line[3] - '1';
    end.x = line[5] - 'A';
    end.y = line[6] - '1';
    boat.start = &start;
    boat.end = &end;
    boat.len = line[0] - '0';
    if (load_boat(game, &boat) != 0)
        return -1;
    return 0;
}

int parse_file(game_t *game)
{
    FILE *stream;
    char *line = NULL;
    int rt_val = 0;
    size_t buff_value = 0;

    if (game == NULL || game->map_script_path == NULL)
        return -1;
    stream = fopen(game->map_script_path, "r");
    if (stream == NULL)
        return -1;
    for (; getline(&line, &buff_value, stream) > 0;) {
        rt_val = analyze_line(game, line);
        if (rt_val != 0)
            return rt_val;
    }
    free(line);
    fclose(stream);
    return 0;
}
