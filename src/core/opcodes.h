#ifndef CORE_OPCODES_H__
#define CORE_OPCODES_H__

#include "chip8.h"
#include <stdint.h>

int op_0x1NNN_jump(struct chip8_t* chip8, uint16_t address);

int op_0x7XNN_add(struct chip8_t* chip8, uint8_t register_index, uint8_t value);

int op_0x8XY0_load(struct chip8_t* chip8, uint8_t reg_x, uint8_t reg_y);

#endif // CORE_OPCODES_H__
