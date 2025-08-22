cmake_minimum_required(VERSION 3.15...4.0)
project(Chip8 VERSION 0.0.1
	      DESCRIPTION "Chip8 interpreter"
	      LANGUAGES C)

add_executable(chip8 src/main.c)

