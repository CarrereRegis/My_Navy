/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** my_tests header
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "../include/str_utils.h"
#include "../include/render.h"

static
void my_memcpy(void *dest, void *src, size_t n)
{
    char *csrc = (char *) src;
    char *cdest = (char *) dest;

    for (int i = 0; i < n; i += 1)
        cdest[i] = csrc[i];
}

Test(unit_test, my_putstr_stderr, .init = cr_redirect_stderr) {
    my_putstr_stderr("Example of error message\n");
    cr_assert_stderr_eq_str("Example of error message\n");
}

Test(unit_test, render_map, .init = cr_redirect_stdout) {
    game_t game = {0};
    char map[MAP_SIZE][MAP_SIZE] =
        {{'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '2', '.', '.', '.', '.', '.', '.'},
        {'.', '2', '.', '4', '4', '4', '4', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '3', '3', '3', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.', '.'}};

    my_memcpy(game.map, map, sizeof(map));
    render_map(game.map);
    cr_assert_stdout_eq_str(""
        " |A B C D E F G H\n"
        "-+---------------\n"
        "1|. . . . . . . .\n"
        "2|. 2 . . . . . .\n"
        "3|. 2 . 4 4 4 4 .\n"
        "4|. . . . . . . .\n"
        "5|. . . . . . . .\n"
        "6|. . 3 3 3 . . .\n"
        "7|. . . . . . . .\n"
        "8|. . . . . . . .\n");
}
