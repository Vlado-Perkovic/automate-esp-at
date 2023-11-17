#ifndef NETWORK_H
#define NETWORK_H

#include <stdio.h>
#include <unistd.h>

#define SERVER_PORT 8080

/**
 * @brief enum for network errors
 *
 */
typedef enum
{
    NETWORK_OK = 0,
    NETWORK_ERR = -1
} network_err_t;

/**
 * @brief function for opening a tcp connection
 *
 * @param sock_fd socket id
 * @param server_ip ip address of the server
 * @param server_port server port
 * @return network_err_t status code
 */
network_err_t network_init_tcp(int32_t *sock_fd, const char *server_ip, uint32_t server_port);

/**
 * @brief function for closing a tcp connection
 *
 * @param sock_fd socket id
 * @return network_err_t status code
 */
network_err_t network_close_tcp(int32_t sock_fd);

#endif // NETWORK_H