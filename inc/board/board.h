#ifndef BOARD_H
#define BOARD_H

#include <stdlib.h>

typedef struct _board_t board_t;

/**
 * @brief enum for board errors
 *
 */
typedef enum
{
    BOARD_OK = 0,
    BOARD_INIT_ERR = -1,
    BOARD_ERR = -2,
} board_err_t;

/**
 * @brief struct for board operations (vtable)
 *
 */
typedef struct
{
    void (*destroy)(board_t *self);
    board_err_t (*set_transparent_mode)(board_t *self);
    board_err_t (*exit_transparent_mode)(board_t *self);
} board_ops_t;

/**
 * @brief struct for board object
 *
 */
struct _board_t
{
    board_ops_t *ops;
};

/**
 * @brief private board init
 *
 * not meant to be used outside the implementation
 *
 * @param self pointer to board object
 * @return board_err_t status code
 */
board_err_t _board_init(board_t *self);

/**
 * @brief board destructor
 *
 * @param self pointer to board object
 * @return board_err_t status code
 */
board_err_t board_delete(board_t *self);

/**
 * @brief a function that automates setting the transparent mode
 *
 * Runs a series of commands and verifies the response
 * off the esp board
 *
 * @param self pointer to board object
 * @return board_err_t status code
 */
board_err_t board_set_transparent_mode(board_t *self);

/**
 * @brief a function that automates exiting the transparent mode
 *
 * @param self pointer to board object
 * @return board_err_t status code
 */
board_err_t board_exit_transparent_mode(board_t *self);

#endif // BOARD_H