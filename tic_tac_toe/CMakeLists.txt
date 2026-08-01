cmake_minimum_required(VERSION 3.18)
project(Test C)

include_directories(
    ${CMAKE_HOME_DIRECTORY}/src/includes
    ${CMAKE_HOME_DIRECTORY}/src/sources
)

add_executable(
    main
    src/sources/main.c
    src/sources/tic_tac_toe.c
    src/includes/tic_tac_toe.h
)