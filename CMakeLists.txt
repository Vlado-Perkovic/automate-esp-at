cmake_minimum_required(VERSION 3.22)
project(automate-esp-at)

# Define MOCK and BOARD options
# option(MOCK "Enable Mock" ON)
# option(BOARD "Specify ESP Board" "MOCK")

if(NOT DEFINED BOARD)
    set(BOARD "MOCK" CACHE STRING "Specify ESP Board")
endif()

# Check if MOCK or BOARD flags are passed

if(BOARD)
    add_compile_definitions(BOARD=${BOARD})
    if(${BOARD} STREQUAL "MOCK")
        add_compile_definitions(MOCK)
    elseif(${BOARD} STREQUAL "ESP32")
        add_compile_definitions(ESP32)
    elseif(${BOARD} STREQUAL "ESP8266")
        add_compile_definitions(ESP8266)
    else()
        add_compile_definitions(OTHER)
    endif()
endif()


# Check the specific BOARD value and define corresponding preprocessor flags


# Add the executable target
add_executable(automate-esp-at
    main.c
    src/board/board.c
    src/board/esp32.c
    src/board/mock.c
    src/utils/utils.c
    src/serial_comm/serial_comm.c
)

# Include directories
target_include_directories(automate-esp-at PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/board
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/src/serial_comm
)

# Add subdirectories
# add_subdirectory(src/board)
# add_subdirectory(src/serial_comm)

# Linking libraries if needed
# target_link_libraries(automate-esp-at board)
# Set the output directory for the build
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)