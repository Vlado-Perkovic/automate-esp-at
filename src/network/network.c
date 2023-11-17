#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <network/network.h>

network_err_t network_init_tcp(int32_t *sock_fd, const char *server_ip, uint32_t server_port)
{
    network_err_t err = NETWORK_OK;

    struct sockaddr_in server_addr;

    int32_t _sock_fd;

    /* create a socket */
    if ((_sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        err = NETWORK_ERR;
    }

    /* set up the server address struct */
    if (err == NETWORK_OK)
    {
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(server_port);
        if (inet_pton(AF_INET, server_ip, &(server_addr.sin_addr)) <= 0)
        {
            perror("inet_pton");
            close(_sock_fd);
            err = NETWORK_ERR;
        }
    }

    // Connect to the server
    if ((err == NETWORK_OK) && (connect(_sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1))
    {
        perror("Connect");
        close(_sock_fd);
        err = NETWORK_ERR;
    }
    return err;
}

network_err_t network_close_tcp(int32_t sock_fd)
{
    close(sock_fd);
    return NETWORK_OK;
}