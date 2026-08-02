cmake_minimum_required(VERSION 3.18)
project(Test C)

include_directories(
    ${CMAKE_HOME_DIRECTORY}/includes
    ${CMAKE_HOME_DIRECTORY}/sources
)

add_executable(
    main
    sources/main.c
    sources/chess.c
    includes/chess.h
    includes/terminal_graphics.h
    includes/escape_commands.h
)