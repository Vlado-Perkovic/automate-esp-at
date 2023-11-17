#include <utils/utils.h>
#include <string.h>

board_t *utils_choose_board()
{
    board_t *board = NULL;
#ifdef MOCK
    board = (board_t *)board_mock_new();
#elif ESP32
    board = (board_t *)board_esp32_new();
#elif ESP8266
    printf("ERROR: ESP8266 isn't supported yet.\n");
    exit(1);
#else
    board = (board_t *)board_esp32_new();
    printf("WARNING: the board setup is ESP32, it should work fine on other ESP32 boards.\n");
#endif
    return board;
}

void utils_extract_ip_address(const char *response, char *ip_address)
{
    /* note: naive parsing */
    /* find first quotation mark */
    const char *start = strchr(response, '\"');

    if (start == NULL)
    {
        fprintf(stderr, "Error in parsing the IP address.\n");
        return;
    }

    /* step over "\"" */
    start++;

    /* find first quotation mark */
    const char *end = strchr(start, '\"');

    if (end == NULL)
    {
        fprintf(stderr, "Error in parsing the IP address.\n");
        return;
    }

    /* copy and terminate the string */
    size_t length = end - start;

    strncpy(ip_address, start, length);
    ip_address[length] = '\0';
}
