/*
** EPITECH PROJECT, 2024
** B-PSU-100-BDX-1-1-navy-antoine.candelon
** File description:
** connection_handler_extra header
*/

#include <stddef.h>

#include "../include/connection_handler_extra.h"
#include "../include/connection_io.h"

void send_hit(connection_t *con, bool hit)
{
    if (con == NULL || con->writing)
        return;
    send_msg(con->remote_pid, HIT_BASE_MSG + (hit ? 1 : 0));
    wait_for_msg(con);
}

bool wait_for_hit(connection_t *con)
{
    int retrieve_val;

    if (con == NULL)
        return false;
    retrieve_val = wait_for_msg(con);
    if (retrieve_val == HIT_BASE_MSG) {
        send_msg(con->remote_pid, ACKN_MSG);
        return false;
    }
    if (retrieve_val == HIT_BASE_MSG + 1) {
        send_msg(con->remote_pid, ACKN_MSG);
        return true;
    }
    return false;
}

void send_eog(connection_t *con, bool has_ended)
{
    if (con == NULL || con->writing)
        return;
    send_msg(con->remote_pid, EOG_BASE_MSG + (has_ended ? 1 : 0));
    wait_for_msg(con);
}

bool wait_for_eog(connection_t *con)
{
    int retrieve_val;

    if (con == NULL)
        return false;
    retrieve_val = wait_for_msg(con);
    if (retrieve_val == EOG_BASE_MSG) {
        send_msg(con->remote_pid, ACKN_MSG);
        return false;
    }
    if (retrieve_val == EOG_BASE_MSG + 1) {
        send_msg(con->remote_pid, ACKN_MSG);
        return true;
    }
    return false;
}
