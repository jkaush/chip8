cmake_minimum_required(VERSION 3.15...4.0)
project(Chip8 VERSION 0.0.1
              DESCRIPTION "Chip8 interpreter"
              LANGUAGES C)

add_executable(chip8 src/main.c
                     src/core/chip8.h
                     src/core/chip8.c)
target_include_directories(chip8 PUBLIC src/)

add_executable(test_chip8 tests/test_chip8.c src/core/chip8.h src/core/chip8.c)
target_include_directories(test_chip8 PUBLIC src/)
