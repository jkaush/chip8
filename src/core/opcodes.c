#include "opcodes.h"
#include "errors.h"
#include <stdint.h>

int op_0x1NNN_jump(struct chip8_t* chip8, uint16_t address)
{
    if (address > 0xFFF || address < 0x200) {
        return -EC8_FAULT; // Invalid address
    }
    chip8->program_counter = address;
    return 0;
}

int op_0x7XNN_add(struct chip8_t* chip8, uint8_t register_index, uint8_t value)
{
    chip8->v_registers[register_index] += value;
    return 0;
}
