#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <board/board.h>
#include <board/esp32.h>
#include <board/mock.h>

/**
 * @brief a function that chooses the right board
 *
 * based on compile time flags, it instantiates and returns
 * a pointer to the board object.
 *
 * @return board_t* pointer to a board object
 */
board_t *utils_choose_board();

#endif // UTILS_H