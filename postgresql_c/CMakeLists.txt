cmake_minimum_required(VERSION 3.18)
project(test_psql LANGUAGES C)

find_package(PostgreSQL REQUIRED)

add_executable(main main.c)
target_include_directories(main PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${PostgreSQL_LIBRARIES})