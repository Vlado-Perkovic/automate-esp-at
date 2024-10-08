#include <stdio.h>
#include <board/board.h>
#include <serial_comm/serial_comm.h>
#include <utils/utils.h>
#include <network/network.h>

#define CMD_SIZE 20

/* private function prototypes */

/**
 * @brief a default method for setting up the transparent mode
 *
 * since the majority of the boards share this method, it made sense to assign a default
 * method.
 *
 * @param self pointer to the board object
 * @return board_err_t status code
 */
board_err_t _board_set_transparent_mode_default(board_t *self);

/**
 * @brief a default method for exiting the transparent mode
 *
 * same reasoning as above.
 *
 * @param self pointer to the board object
 * @return board_err_t status code
 */
board_err_t _board_exit_transparent_mode_default(board_t *self);

board_ops_t default_ops = {
    .destroy = NULL,
    .set_transparent_mode = _board_set_transparent_mode_default,
    .exit_transparent_mode = _board_exit_transparent_mode_default,
};

/* public functions */

board_err_t _board_init(board_t *self)
{

    if (self == NULL)
    {
        fprintf(stderr, "Bad board pointer.\n");
        return BOARD_ERR;
    }

    self->ops = &default_ops;
    self->fd = -1;
    self->sock_fd = -1;

    return BOARD_OK;
}

board_err_t board_delete(board_t *self)
{
    board_err_t err = OK;

    if (self == NULL)
    {
        fprintf(stderr, "Bad board pointer.\n");
        err = BOARD_ERR;
    }

    if ((err == BOARD_OK) && (self->ops->destroy))
    {
        self->ops->destroy(self);
    }
    if ((err == BOARD_OK))
    {

        free(self);
    }
    return err;
}

board_err_t board_set_transparent_mode(board_t *self)
{
    board_err_t err = OK;
    if (self == NULL)
    {
        fprintf(stderr, "Bad board pointer.\n");
        err = BOARD_ERR;
    }

    if ((err == BOARD_OK) && self->ops && self->ops->set_transparent_mode)
    {
        err = self->ops->set_transparent_mode(self);
    }

    return err;
}

board_err_t board_exit_transparent_mode(board_t *self)
{
    board_err_t err = OK;
    if (self == NULL)
    {
        fprintf(stderr, "Bad board pointer.\n");
        err = BOARD_ERR;
    }

    if ((err == BOARD_OK) && self->ops && self->ops->exit_transparent_mode)
    {
        err = self->ops->exit_transparent_mode(self);
    }

    return err;
}

/* private functions */

board_err_t _board_set_transparent_mode_default(board_t *self)
{
    /* https://docs.espressif.com/projects/esp-at/en/release-v2.4.0.0/esp32/AT_Command_Examples/TCP-IP_AT_Examples.html#uart-wi-fi-passthrough-transmission-when-the-esp32-works-as-a-tcp-server */
    serial_comm_err_t err = OK;

    err = serial_comm_send_command("AT+CWMODE=1", "OK", NULL, self->fd);

    if (err == OK)
    {
        err = serial_comm_send_command("AT+CWJAP=\"espressif\",\"1234567890\"", "OK", NULL, self->fd);
    }

    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPMUX=1", "OK", NULL, self->fd);
    }
    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPSERVERMAXCONN=1", "OK", NULL, self->fd);
    }
    if (err == OK)
    {
        /* format the command based on the defined port */
        char command[CMD_SIZE];
        snprintf(command, sizeof(command), "AT+CIPSERVER=1,%d", SERVER_PORT);
        err = serial_comm_send_command(command, "OK", NULL, self->fd);
    }
    char response[RESPONSE_SIZE];
    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPSTA?", "OK", response, self->fd);
    }
#ifndef MOCK

    utils_extract_ip_address(response, self->ip_address);

    if (network_init_tcp(&self->sock_fd, self->ip_address, SERVER_PORT) != NETWORK_OK)
    {
        err = SEND_ERR;
        fprintf(stderr, "TCP connection failed.\n");
    }

    /* important to wait for the connected signal */
    if (err == OK)
    {
        err = serial_comm_receive_serial(response, RESPONSE_SIZE, self->fd);
    }
#endif

    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPMODE=1", "OK", NULL, self->fd);
    }
    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPSEND", "OK", NULL, self->fd);
    }

    if (err != OK)
    {
        return BOARD_ERR;
    }
    printf("TRANSPARENT MODE SET SUCCESSFULLY.\n");
    printf("to exit we need to send +++\n");

    return BOARD_OK;
}

board_err_t _board_exit_transparent_mode_default(board_t *self)
{
    serial_comm_err_t err = OK;
    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPMODE=0", "OK", NULL, self->fd);
    }
    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPCLOSE", "OK", NULL, self->fd);
    }

#ifndef MOCK
    if (network_close_tcp(self->sock_fd) != NETWORK_OK)
    {
        err = SEND_ERR;
    }
#endif

    if (err != OK)
    {
        return BOARD_ERR;
    }
    printf("TRANSPARENT MODE EXITED SUCCESSFULLY.\n");

    return BOARD_OK;
}
