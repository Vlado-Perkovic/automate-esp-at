#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>

#include <serial_comm/serial_comm.h>

serial_comm_err_t serial_comm_init(const serial_config_t *config, int32_t *fd)
{

    serial_comm_err_t err = OK;

    int32_t _fd = open(config->device_path, O_RDWR | O_NOCTTY);
    if (_fd < 0)
    {
        perror("Error opening serial port");
        err = INIT_ERR;
    }
    struct termios tty;
    if ((err == OK) && (tcgetattr(_fd, &tty) != 0))
    {
        perror("Error from tcgetattr");
        err = INIT_ERR;
    }

    if (err == OK)
    {
        cfsetospeed(&tty, config->baud_rate);
        cfsetispeed(&tty, config->baud_rate);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | config->data_bits;
        tty.c_cflag |= CLOCAL | CREAD;
        // Ignore modem control lines, enable reading

        // Set stop bits
        switch (config->stop_bits)
        {
        case 1:
            tty.c_cflag &= ~CSTOPB;
            break;
        case 2:
            tty.c_cflag |= CSTOPB;
            break;
        default:
            fprintf(stderr, "Invalid stop bits configuration\n");
            err = INIT_ERR;
        }
    }

    if ((err == OK) && (tcsetattr(_fd, TCSANOW, &tty) != 0))
    {
        perror("Error from tcsetattr");
        err == INIT_ERR;
    }

    if (err == OK)
    {
        *fd = _fd;
    }

    return err;
}

void serial_comm_close(int32_t fd)
{
    close(fd);
}

serial_comm_err_t serial_comm_send_serial(const char *msg, int32_t fd)
{
    serial_comm_err_t err = OK;

#if defined(ESP32) || defined(ESP8266) || defined(OTHER)
    // TODO:
    printf("TODO:\n");
#elif MOCK
    FILE *file = fopen("esp32.txt", "w");
    if (file == NULL)
    {
        perror("Error opening file for writing");
        err = SEND_ERR;
    }

    if (err == OK)
    {
        fprintf(file, "%s\n", msg);
        fclose(file);
    }

#else
    printf("Specify a BOARD flag among the supported boards. The default state is MOCK.\n");
    err = SEND_ERR;
#endif
    return err;
}

serial_comm_err_t serial_comm_receive_serial(char *response, uint8_t response_size, int32_t fd)
{
    serial_comm_err_t err = OK;
#if defined(ESP32) || defined(ESP8266) || defined(OTHER)
    // TODO:
    printf("TODO:\n");
    // size_t bytes_written = write()
#elif MOCK
    FILE *file = fopen("esp32.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file for reading");
        err = RECEIVE_ERR;
    }
    if (err == OK)
    {
        fseek(file, 0, SEEK_SET);

        fgets(response, response_size, file);

        ftruncate(fileno(file), 0);

        fclose(file);
    }
#else
    printf("Specify a BOARD flag among the supported boards. The default state is MOCK.\n");
    err = RECEIVE_ERR;
#endif
    return err;
}

serial_comm_err_t serial_comm_send_command(const char *command, const char *expected_response, char *response, int32_t fd)
{
    serial_comm_err_t err = OK;

    char res[50];

    err = serial_comm_send_serial(command, fd);

    /* TODO: POLL FOR ANSWER INSTEAD OF SLEEPING */
    usleep(10000);

    if (err == OK)
    {
        err = serial_comm_receive_serial(res, sizeof(res), fd);
    }

    if ((err == OK) && (strstr(res, expected_response) == NULL))
    {
        fprintf(stderr, "Expected outcome was: %s, but got: %s\n", expected_response, res);
        err = RECEIVE_ERR;
    }

    if ((err == OK) && (response != NULL))
    {
        strcpy(response, res);
    }

    return err;
}
