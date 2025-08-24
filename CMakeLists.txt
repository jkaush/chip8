cmake_minimum_required(VERSION 3.15...4.0)
project(Chip8 VERSION 0.0.1
              DESCRIPTION "Chip8 interpreter"
              LANGUAGES C)

find_package(check REQUIRED)
find_package(SDL3 REQUIRED)

add_executable(chip8 src/main.c
                     src/core/chip8.h
                     src/core/chip8.c
                     src/core/opcodes.h
                     src/core/opcodes.c
                     src/core/errors.h)
target_include_directories(chip8 PUBLIC src/)
target_link_libraries(chip8 PRIVATE SDL3::SDL3)

add_executable(test_chip8 tests/test_opcodes.c
                          src/core/chip8.h
                          src/core/chip8.c
                          src/core/opcodes.h
                          src/core/opcodes.c
                          src/core/errors.h)
target_include_directories(test_chip8 PUBLIC src/)
target_link_libraries(test_chip8 PRIVATE check)
