/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** destroyer header
*/

#include <malloc.h>

#include "destroyer.h"

void destroy_game_content(game_t *game)
{
    free(game->map_script_path);
}
