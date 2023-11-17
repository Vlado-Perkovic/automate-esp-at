#include <board/board.h>
#include <board/mock.h>

#include <stdio.h>

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
