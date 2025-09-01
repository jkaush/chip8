#include "core/chip8.h"
#include <stdio.h>
#include <string.h>

int main()
{
    struct chip8_t chip8;
    chip8_initialize(&chip8);
    static const uint8_t expected_memory[4096] = {0};
    static const uint16_t expected_stack[16] = {0};
    if (memcmp(chip8.memory, expected_memory, font_offset) != 0) {
        printf("Initial memory not zeroed.\n");
        return 1;
    }
    if (memcmp(chip8.memory + font_offset,
           chip8_fontset,
           sizeof(chip8_fontset)) != 0) {
        printf("Font loaded incorrectly.\n");
        return 1;
    }
    if (memcmp(chip8.memory + font_offset + sizeof(chip8_fontset),
           expected_memory,
           sizeof(chip8.memory) - sizeof(chip8_fontset)
            - font_offset) != 0) {

        printf("Rest of memory not zeroed.\n");
        return 1;
    }
    if (memcmp(chip8.stack, expected_stack, sizeof(chip8.stack)) != 0) {
        printf("Stack not zeroed.\n");
        return 1;
    }
    if (memcmp(chip8.V,
               expected_memory,
               sizeof(chip8.V)) != 0) {
        printf("V Registers not zeroed.\n");
        return 1;
    }
    if (chip8.pc != 0x200) {
        printf("Program counter incorrectly set.\n");
        return 1;
    }
    if (chip8.sp != 0) {
        printf("Stack pointer incorrectly set.\n");
        return 1;
    }
    if (chip8.delay_timer != 0) {
        printf("Delay timer incorrectly set.\n");
        return 1;
    }
    if (chip8.sound_timer != 0) {
        printf("Sound timer incorrectly set.\n");
        return 1;
    }
    if (chip8.I != 0) {
        printf("Index register incorrectly set.\n");
        return 1;
    }
    printf("All checks passed.\n");
    return 0;
}