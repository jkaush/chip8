#ifndef CORE_OPCODES_H__
#define CORE_OPCODES_H__

#include "chip8.h"
#include <stdint.h>

void op_0x00E0_clear_screen(struct chip8_t* chip8);
void op_0x1NNN_jump(struct chip8_t* chip8, uint16_t address);

void op_0x6XNN_set_register(struct chip8_t* chip8, uint8_t register_index, uint8_t value);

// Does not set carry flag
void op_0x7XNN_add(struct chip8_t* chip8, uint8_t register_index, uint8_t value);

int op_0x8XY0_load(struct chip8_t* chip8, uint8_t reg_x, uint8_t reg_y);

void op_0xANNN_set_index(struct chip8_t* chip8, uint16_t nnn);

void op_0xDXYN_draw(struct chip8_t* chip8, uint8_t x, uint8_t y, uint8_t n);

#endif // CORE_OPCODES_H__
