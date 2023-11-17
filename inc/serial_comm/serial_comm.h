#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include <stdint.h>

typedef enum
{
    OK = 0,
    SEND_ERR = -1,
    RECEIVE_ERR = -2,
    INIT_ERR = -3,
} serial_comm_err_t;

typedef struct
{
    const char *device_path;
    uint32_t baud_rate;
    uint8_t stop_bits;
    uint8_t data_bits;
} serial_config_t;

/**
 * @brief function for initializing the serial communication
 *
 * opens the device file, sets the parameters of the channel
 *
 * @param config config struct
 * @param fd file descriptor
 * @return serial_comm_err_t status code
 */
serial_comm_err_t serial_comm_init(const serial_config_t *config, int32_t *fd);

/**
 * @brief function for closing the file descriptor
 *
 * @param fd file descriptor
 */
void serial_comm_close(int32_t fd);

/**
 * @brief function for sending a string to the serial connection
 *
 * @param msg string data
 * @return serial_comm_err_t status code
 */
serial_comm_err_t serial_comm_send_serial(const char *msg, int32_t fd);

/**
 * @brief function for receiving a string from the serial connection
 *
 * @param response string data
 * @return serial_comm_err_t status code
 */
serial_comm_err_t serial_comm_receive_serial(char *response, uint8_t response_size, int32_t fd);

/**
 * @brief function that querys the device on the serial connection and checks the response
 *
 * @param command a string that is sent to the device
 * @param expected_response a string that is expected
 * @return serial_comm_err_t status code
 */
serial_comm_err_t serial_comm_send_command(const char *command, const char *expected_response, char *response, int32_t fd);

#endif // SERIAL_COMM_H