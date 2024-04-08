/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** my_parser header
*/

#include "../include/my_navy.h"

#ifndef B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_MY_PARSER_H
    #define B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_MY_PARSER_H
    #define NORMAL_LINE_LEN 7
    #define CHAR_A_TO_H(c) ((c) >= 'A' && (c) <= 'H')
    #define MIN(a, b) ((b) > (a) ? (a) : (b))
int parse_file(game_t *game);
typedef struct {
    vector_2i_t *start;
    vector_2i_t *end;
    int len;
} boat_t;
#endif //B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_MY_PARSER_H
