/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** connection_handler_extra header
*/

#include "../include/connection_handler.h"

#ifndef B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_CONNECTION_HANDLER_EXTRA_H
    #define B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_CONNECTION_HANDLER_EXTRA_H
    #define HIT_BASE_MSG 10
    #define EOG_BASE_MSG 15
void send_hit(connection_t *con, bool hit);
bool wait_for_hit(connection_t *con);
void send_eog(connection_t *con, bool has_ended);
bool wait_for_eog(connection_t *con);
#endif //B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_CONNECTION_HANDLER_EXTRA_H
