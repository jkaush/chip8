#ifndef CORE_OPCODES_H__
#define CORE_OPCODES_H__

#include "chip8.h"
#include <stdint.h>

int op_0x1NNN_jump(struct chip8_t* chip8, uint16_t address);

#endif // CORE_OPCODES_H__
