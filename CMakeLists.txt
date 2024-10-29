cmake_minimum_required(VERSION 3.10)

project(CANanalyzer)

set(CMAKE_C_STANDART 99)
set(CMAKE_C_STANDART_REQUIRED True)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS$} -static")

set(SOURCE_FILES
    src/checking_err.c
    src/main.c
    )

set(HEADER_FILES
    include/checking_err.h
    include/main.h
    )

add_executable(CANanalyzer ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(CANanalyzer PUBLIC ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
