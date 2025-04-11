cmake_minimum_required(VERSION 3.5)
project(vigenere_cryptanalysis)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
# set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)
set(MAIN_DIR ${CMAKE_SOURCE_DIR}/main)

set(SOURCES
    ${SOURCE_DIR}/key_recovery.cpp
    ${SOURCE_DIR}/length_recovery.cpp
    ${SOURCE_DIR}/read_text.cpp
)

include_directories(${SOURCE_DIR})

add_executable(key_recovery ${MAIN_DIR}/key_recovery_driver.cpp ${SOURCES})
add_executable(vigenere ${MAIN_DIR}/vigener.cpp)