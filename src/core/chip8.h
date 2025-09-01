#ifndef CORE_CHIP8_H__
#define CORE_CHIP8_H__

#include <stdbool.h>
#include <stdint.h>

#define MEMORY_SIZE 4096
#define STACK_DEPTH 16
#define V_REGISTER_COUNT 16
#define PC_START 0x200

#define CHIP8_WIDTH 64
#define CHIP8_HEIGHT 32

extern const uint8_t chip8_fontset[80];
extern const uint16_t font_offset;

struct chip8_t {
    uint8_t memory[MEMORY_SIZE]; // 4K memory
    uint8_t V[V_REGISTER_COUNT]; // V0 to VF registers
    uint16_t pc;                 // Program counter
    uint16_t I;                  // Index register
    uint16_t stack[STACK_DEPTH]; // Call stack
    uint8_t sp;                  // Stack pointer

    // Timers
    uint8_t delay_timer;
    uint8_t sound_timer;

    // Input/Output
    uint8_t keypad[16]; // Hex-based keypad (0x0-0xF)
    uint32_t gfxbuffer[CHIP8_WIDTH * CHIP8_HEIGHT]; // Graphics buffer
    bool draw_flag; // Indicates if the screen needs to be redrawn

    uint8_t screen[CHIP8_WIDTH][CHIP8_HEIGHT];
};

void chip8_initialize(struct chip8_t* chip8);

#endif // CORE_CHIP8_H__
