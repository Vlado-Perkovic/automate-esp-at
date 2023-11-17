#include <board/board.h>
#include <board/esp32.h>
#include <board/mock.h>
#include <utils/utils.h>
#include <serial_comm/serial_comm.h>

#define DEVICE_PATH "/dev/ttyUSB0"
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1

int main()
{
    board_t *board = utils_choose_board();

    serial_config_t config = {.device_path = DEVICE_PATH,
                              .baud_rate = BAUD_RATE,
                              .data_bits = DATA_BITS,
                              .stop_bits = STOP_BITS};

    serial_comm_init(&config, &board->fd);

    // if (board_set_transparent_mode(board) != BOARD_OK)
    // {

    //     fprintf(stderr, "Set transparent mode failed.\n");
    //     return -1;
    // }
    // if (board_exit_transparent_mode(board) != BOARD_OK)
    // {

    //     fprintf(stderr, "Exit transparent mode failed.\n");
    //     return -1;
    // }

    serial_comm_close(board->fd);
    board_delete(board);
    return 0;
}
