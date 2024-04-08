/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** connection_IO header
*/

#include <malloc.h>
#include <time.h>
#include <unistd.h>

#include "../include/connection_io.h"
#include "str_utils.h"

/**
 * Send a seperator bit to the remote process
 * @param pid the pid of the remote process
 */
static
void send_separator(int pid)
{
    struct timespec wait_time = WAIT_BTW_SIG;

    kill(pid, SIGUSR2);
    nanosleep(&wait_time, &wait_time);
}

/**
 * Send a data bit to the remote process
 * @param pid the pid of the remote process
 */
static
void send_bit(int pid)
{
    struct timespec wait_time = WAIT_BTW_SIG;

    kill(pid, SIGUSR1);
    nanosleep(&wait_time, &wait_time);
}

/**
 * Wait for a message to arrive and return the value of the message
 * @param con the connection data type
 * @return the value of the received message
 * @return -1 if the connection failed
 */
int wait_for_msg(connection_t *con)
{
    int tmp;

    pause();
    while (con->writing) {
        pause();
        if (con->is_active == false) {
            my_putstr_stderr("Error: Connection lost\n");
            return -1;
        }
    }
    tmp = con->nb_sigusr1_received;
    con->nb_sigusr1_received = 0;
    return tmp;
}

/**
 * Send a message to the remote
 * @param pid the pid of the remote process
 * @param msg the value of the message
 */
void send_msg(int pid, int msg)
{
    send_separator(pid);
    for (int i = 0; i < msg; i += 1)
        send_bit(pid);
    send_separator(pid);
}

/**
 * Close the connection and free its struct
 * @param connection the connection data type
 */
void close_connection(connection_t *connection)
{
    connection->is_active = false;
    free(connection);
}
