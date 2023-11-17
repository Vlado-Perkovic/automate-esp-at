#ifndef ESP32_H
#define ESP32_H

#include <board/board.h>
#include <stdbool.h>

/**
 * @brief struct for esp32 object derived from board object
 *
 */
typedef struct
{
    board_t base;

} board_esp32_t;

/**
 * @brief static constructor for esp32 board object
 *
 * @param self pointer to a esp32 board object
 * @return true if successful
 * @return false otherwise
 */
bool board_esp32_init(board_esp32_t *self);

/**
 * @brief dynamic constructor for esp32 board object
 *
 * @return board_esp32_t* pointer to a esp32 board object
 */
board_esp32_t *board_esp32_new();

#endif // ESP32_H