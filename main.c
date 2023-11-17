#include <board/board.h>
#include <board/esp32.h>
#include <board/mock.h>
#include <utils/utils.h>
#include <serial_comm/serial_comm.h>

int main()
{
    board_t *board = utils_choose_board();

    if (board_set_transparent_mode(board) != BOARD_OK)
    {

        fprintf(stderr, "Set transparent mode failed.\n");
        return -1;
    }
    if (board_exit_transparent_mode(board) != BOARD_OK)
    {

        fprintf(stderr, "Exit transparent mode failed.\n");
        return -1;
    }

    board_delete(board);
    return 0;
}
