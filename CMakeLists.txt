# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
#include(ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
include(pico_sdk_import.cmake)
include(pico_extras_import.cmake)


# Set name of project (as PROJECT_NAME) and C/C   standards
project(demo01 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

include(${CMAKE_CURRENT_LIST_DIR}/picosystem_hardware/picosystem_hardware.cmake REQUIRED)


# Tell CMake where to find the executable source file
#add_executable(${PROJECT_NAME} 
#  main.c
#)
# Create map/bin/hex/uf2 files
#pico_add_extra_outputs(${PROJECT_NAME})

function(picosystem_hardware_executable NAME SOURCES)

  add_executable(
    ${NAME}
    ${SOURCES}
    ${ARGN}
  )

  # Pull in pico libraries that we need
  target_link_libraries(${NAME} picosystem_hardware)
  # Link to pico_stdlib (gpio, time, etc. functions)
  target_link_libraries(${NAME} pico_stdlib)

  # Enable usb output, disable uart output
  pico_enable_stdio_usb(${NAME} 0)
  pico_enable_stdio_uart(${NAME} 1)
  
  # create map/bin/hex file etc.
  pico_add_extra_outputs(${NAME})

  pico_set_linker_script(${NAME} ${picosystem_hardware_LINKER_SCRIPT})

  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2 DESTINATION .)
endfunction()

picosystem_hardware_executable(
    ${PROJECT_NAME}
    main.cpp
)



# Enable usb output, disable uart output
# Same settings exists in picosystem_hardware.cmake
#pico_enable_stdio_usb(${PROJECT_NAME} 0)
#pico_enable_stdio_uart(${PROJECT_NAME} 1)
