/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** my_navy header
*/

#ifndef B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_MY_NAVY_H
    #define B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_MY_NAVY_H
    #include "connection_handler.h"
    #define EXIT_FAILURE_TECH 84
    #define MAP_SIZE 8
int my_navy(int argc, char **argv);
typedef enum {
    UNKNOWN = 0,
    CLIENT = 1,
    SERVER = 2
} con_mode_t;
typedef enum {
    LOCAL,
    REMOTE
} turn_status_t;
typedef struct {
    connection_t *con;
    char map[MAP_SIZE][MAP_SIZE];
    char remote_map[MAP_SIZE][MAP_SIZE];
    char *map_script_path;
    con_mode_t mode;
    bool playing;
    turn_status_t current_turn;
} game_t;
#endif //B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_MY_NAVY_H
