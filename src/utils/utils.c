#include <utils/utils.h>

board_t *utils_choose_board()
{
    board_t *board = NULL;
#ifdef MOCK
    board = (board_t *)board_mock_new();
#elif ESP32
    board = (board_t *)board_esp32_new();
#elif ESP8266
    // board = (board_t *)board_esp32_new();
    printf("ERROR: ESP8266 isn't supported yet.\n");
#else
    board = (board_t *)board_esp32_new();
    printf("WARNING: the board setup is ESP32, it should work fine on other ESP32 boards.\n");
#endif
    return board;
}
