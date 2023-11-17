#include <board/board.h>
#include <board/esp32.h>

#include <stdio.h>

#include <serial_comm/serial_comm.h>

static void _board_esp32_set_transparent_mode(board_t *self);

// constructor
board_esp32_t *board_esp32_new()
{
    board_esp32_t *self = (board_esp32_t *)malloc(sizeof(board_esp32_t));
    if (self)
    {
        if (!board_esp32_init(self))
        {
            free(self);
            self = NULL;
        }
    }
    return self;
}

bool board_esp32_init(board_esp32_t *self)
{
    _board_init(&self->base);
    return true;
}
