#include <board/board.h>
#include <board/mock.h>

#include <stdio.h>

// #include <serial_comm/serial_comm.h>

static void _board_mock_set_transparent_mode(board_t *self);

// constructor
board_mock_t *board_mock_new()
{
    board_mock_t *self = (board_mock_t *)malloc(sizeof(board_mock_t));
    if (self)
    {
        if (!board_mock_init(self))
        {
            free(self);
            self = NULL;
        }
    }
    return self;
}

bool board_mock_init(board_mock_t *self)
{
    _board_init(&self->base);
    return true;
}
