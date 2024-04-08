/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** connection_handler header
*/

#ifndef B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_CONNECTION_HANDLER_H
    #define B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_CONNECTION_HANDLER_H
    #include <signal.h>
    #include <stdbool.h>
    #define WAIT_BTW_SIG ((struct timespec) {0, 500000})
    #define INIT_MSG 2
    #define ACKN_MSG 1
    #define EOG_MSG 0
typedef struct {
    bool is_active;
    bool writing;
    int remote_pid;
    int nb_sigusr1_received;
} connection_t;
typedef struct {
    int x;
    int y;
} vector_2i_t;
connection_t *init_connection(int pid);
connection_t *wait_for_connection(void);
void send_pos(connection_t *con, vector_2i_t *pos);
vector_2i_t *wait_for_pos(connection_t *con);
#endif //B_PSU_100_BDX_1_1_NAVY_ANTOINE_CANDELON_CONNECTION_HANDLER_H
