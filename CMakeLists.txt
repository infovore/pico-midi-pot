cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(test_project C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
pico_sdk_init()

add_executable(pico-midi-pot
  pico-midi-pot.c
  usb_descriptors.c
)

pico_enable_stdio_usb(pico-midi-pot 0)
pico_enable_stdio_uart(pico-midi-pot 1)

target_include_directories(pico-midi-pot PRIVATE ${CMAKE_CURRENT_LIST_DIR})

pico_add_extra_outputs(pico-midi-pot)
target_link_libraries(pico-midi-pot PRIVATE pico_stdlib hardware_adc tinyusb_device tinyusb_board)
