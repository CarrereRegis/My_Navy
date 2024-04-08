/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** str_utils header
*/

#include <unistd.h>

#include "../include/str_utils.h"
#include "../include/my.h"

/**
 * Write an str to the STDERR
 * @param str the str to print
 */
long my_putstr_stderr(char *str)
{
    return write(STDERR_FILENO, str, my_strlen(str));
}
