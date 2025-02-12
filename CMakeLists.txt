cmake_minimum_required(VERSION 3.10)
project(gow_compiler C)

set(CMAKE_C_STANDARD 99)

include_directories(interfaces)

add_executable(gow_compiler main.c
        src/interpreter.c
        src/lexer.c
        src/parser.c
)
