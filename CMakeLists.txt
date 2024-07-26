cmake_minimum_required(VERSION 3.5.0)

project(
    algorithm_for_c VERSION 0.0.2
    DESCRIPTION "C language algorithm collection"
    LANGUAGES C
)

set(AUTHOR "Dinnerb0ne Ma <tomma_2022@outlook.com>")
set(COPYRIGHT "Copyright (c) 2024 ${AUTHOR}")


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(PROJECT_SOURCE_DIR .)

include_directories(${PROJECT_SOURCE_DIR}/include)
# target_include_directories(algorithm_for_c PRIVATE ${PROJECT_SOURCE_DIR}/include)

# aux_source_directory(SOURCE_DIR ./src)
include_directories(./include)

add_compile_options(-static -std=c11 -Wall -O0)

add_executable(algorithm_for_c  main.c ./src/hashmap.c ./src/sort.c ./src/helper.c)



message(STATUS "Project: ${PROJECT_NAME} version ${PROJECT_VERSION}")
message(STATUS "Description: ${PROJECT_DESCRIPTION}")
message(STATUS "Author: ${AUTHOR}")
message(STATUS "Copyright: ${COPYRIGHT}")
