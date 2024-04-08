/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** connection_handler header
*/

#include <signal.h>
#include <stdlib.h>

#include "../include/connection_handler.h"
#include "../include/connection_io.h"
#include "../include/my_printf.h"
#include "../include/static_con.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-identifier-naming"

/**
 * Handle SIGUSR1 and SIGUSR2 signals
 * @param sig_id the id of the signal received
 * @param info a siginfo_t type with informations about the sender/signal
 * @param ucontext context info saved by the kernel
 */
static
void handle_sigusr(int sig_id, siginfo_t *info,
    __attribute__((unused)) void *ucontext)
{
    if (GLOBAL_CONNECTION->remote_pid == -1)
        GLOBAL_CONNECTION->remote_pid = info->si_pid;
    if (sig_id == SIGUSR2)
        GLOBAL_CONNECTION->writing = !GLOBAL_CONNECTION->writing;
    if (sig_id == SIGUSR1 && GLOBAL_CONNECTION->writing)
        GLOBAL_CONNECTION->nb_sigusr1_received += 1;
    if (sig_id == SIGUSR1 && !GLOBAL_CONNECTION->writing)
        GLOBAL_CONNECTION->is_active = false;
}

/**
 * Load the SIGUSR1 and SIGUSR2 handler
 */
static
int load_handlers(void)
{
    struct sigaction sigusr;

    sigusr.sa_sigaction = handle_sigusr;
    sigemptyset(&sigusr.sa_mask);
    sigusr.sa_flags = SA_SIGINFO;
    if (sigaction(SIGUSR1, &sigusr, NULL) == -1)
        return -1;
    if (sigaction(SIGUSR2, &sigusr, NULL) == -1)
        return -1;
    return 0;
}

/**
 * Establish a connection with the remote process
 * @param pid the pid of the remote process
 * @return the connection data type
 * @return NULL if the connection failed
 */
connection_t *init_connection(int pid)
{
    GLOBAL_CONNECTION = malloc(sizeof(connection_t));
    if (GLOBAL_CONNECTION == NULL || load_handlers() == -1)
        return NULL;
    GLOBAL_CONNECTION->remote_pid = pid;
    GLOBAL_CONNECTION->writing = false;
    GLOBAL_CONNECTION->is_active = true;
    GLOBAL_CONNECTION->nb_sigusr1_received = 0;
    send_msg(pid, INIT_MSG);
    if (wait_for_msg(GLOBAL_CONNECTION) == ACKN_MSG) {
        my_printf("successfully connected\n");
        return GLOBAL_CONNECTION;
    }
    free(GLOBAL_CONNECTION);
    return NULL;
}

/**
 * Wait for a remote process to connect and establish a connection
 * @return the connection data type connect
 * @return NULL if the connection failed
 */
connection_t *wait_for_connection(void)
{
    GLOBAL_CONNECTION = malloc(sizeof(connection_t));
    if (GLOBAL_CONNECTION == NULL)
        return NULL;
    load_handlers();
    GLOBAL_CONNECTION->remote_pid = -1;
    GLOBAL_CONNECTION->writing = false;
    GLOBAL_CONNECTION->is_active = true;
    GLOBAL_CONNECTION->nb_sigusr1_received = 0;
    my_printf("waiting for enemy connection...\n");
    if (wait_for_msg(GLOBAL_CONNECTION) == INIT_MSG) {
        my_printf("enemy connected\n");
        send_msg(GLOBAL_CONNECTION->remote_pid, ACKN_MSG);
        return GLOBAL_CONNECTION;
    }
    free(GLOBAL_CONNECTION);
    return NULL;
}

/**
 * send a pos as a vector_2u to the remote process
 * @param con the connection data type
 * @param pos the position to send
 */
void send_pos(connection_t *con, vector_2i_t *pos)
{
    if (con == NULL || con->writing || !con->is_active)
        return;
    send_msg(con->remote_pid, (int) pos->x + 1);
    send_msg(con->remote_pid, (int) pos->y + 1);
    wait_for_msg(con);
}

/**
 * Wait for the remote to send a pos as a vector_2u
 * @param con the connection data type
 * @return the received vector_2u
 */
vector_2i_t *wait_for_pos(connection_t *con)
{
    vector_2i_t *pos = malloc(sizeof(vector_2i_t));

    if (pos == NULL)
        return NULL;
    pos->x = wait_for_msg(con) - 1;
    pos->y = wait_for_msg(con) - 1;
    send_msg(con->remote_pid, ACKN_MSG);
    return pos;
}

#pragma clang diagnostic pop
