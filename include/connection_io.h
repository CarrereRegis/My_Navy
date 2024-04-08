/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** connection_IO header
*/

#ifndef B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_CONNECTION_IO_H
    #define B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_CONNECTION_IO_H
    #include "connection_handler.h"
int wait_for_msg(connection_t *connection);
void send_msg(int pid, int msg);
void close_connection(connection_t *connection);
#endif //B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_CONNECTION_IO_H
