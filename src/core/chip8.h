#ifndef CORE_CHIP8_H__
#define CORE_CHIP8_H__

#include <stdint.h>

#define MEMORY_SIZE 4096
#define STACK_DEPTH 16
#define V_REGISTER_COUNT 16

#define CHIP8_WIDTH 64
#define CHIP8_HEIGHT 32

extern const uint8_t chip8_fontset[80];
extern const uint16_t font_offset;

struct chip8_t {
    uint8_t memory[MEMORY_SIZE];
    uint8_t v_registers[V_REGISTER_COUNT];
    uint16_t program_counter;
    uint16_t index_register;
    uint16_t stack[STACK_DEPTH];
    uint8_t stack_ptr;
    uint8_t delay_timer;
    uint8_t sound_timer;

    uint8_t screen[CHIP8_WIDTH][CHIP8_HEIGHT];
};

void init_chip8(struct chip8_t* chip8);

#endif // CORE_CHIP8_H__
