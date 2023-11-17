#include <board/board.h>
#include <serial_comm/serial_comm.h>
#include <stdio.h>

/* private function prototypes */
board_err_t _board_set_transparent_mode_default(board_t *self);
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
    serial_comm_err_t err = OK;

    err = serial_comm_send_command("AT+CWMODE=1", "OK", NULL);

    if (err == OK)
    {
        err = serial_comm_send_command("AT+CWJAP=\"espressif\",\"1234567890\"", "OK", NULL);
    }

    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPMUX=1", "OK", NULL);
    }
    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPSERVERMAXCONN=1", "OK", NULL);
    }
    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPSERVER=1,8080", "OK", NULL);
    }
    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPSTA?", "OK", NULL); /* TODO: QUERY THE RESPONSE */
    }
    /* TODO: CONNECT THE PC TO THE INTERNET */
    /* TODO: WAIT FOR THE AT RESPONSE */
    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPMODE=1", "OK", NULL);
    }
    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPSEND", "OK", NULL);
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
        err = serial_comm_send_command("AT+CIPMODE=0", "OK", NULL);
    }
    if (err == OK)
    {
        err = serial_comm_send_command("AT+CIPCLOSE", "OK", NULL);
    }

    if (err != OK)
    {
        return BOARD_ERR;
    }
    printf("TRANSPARENT MODE EXITED SUCCESSFULLY.\n");

    return BOARD_OK;
}
