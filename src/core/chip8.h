#ifndef CORE_CHIP8_H__
#define CORE_CHIP8_H__

#include <stdint.h>

extern const uint8_t chip8_fontset[80];
extern const uint16_t font_offset;

struct chip8_t {
    uint8_t memory[4096];
    uint8_t v_registers[16];
    uint16_t program_counter;
    uint16_t index_register;
    uint16_t stack[16];
    uint8_t stack_ptr;
    uint8_t delay_timer;
    uint8_t sound_timer;
};

void init_chip8(struct chip8_t* chip8);

#endif // CORE_CHIP8_H__
