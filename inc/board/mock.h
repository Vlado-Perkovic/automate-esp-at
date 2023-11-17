#ifndef MOCK_H
#define MOCK_H

#include <board/board.h>
#include <stdbool.h>

/**
 * @brief struct for mock object derived from board object
 *
 */
typedef struct
{
    board_t base;

} board_mock_t;

/**
 * @brief static constructor for mock board object
 *
 * @param self pointer to a mock board object
 * @return true if successful
 * @return false otherwise
 */
bool board_mock_init(board_mock_t *self);

/**
 * @brief dynamic constructor for mock board object
 *
 * @return board_mock_t* pointer to a mock board object
 */
board_mock_t *board_mock_new();

#endif // MOCK_H