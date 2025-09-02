#include "acutest.h"
#include "core/chip8.h"
#include "core/opcodes.h"

void test_op_00E0(void) {
    struct chip8_t chip8;
    chip8_initialize(&chip8);
    chip8.gfxbuffer[0] = 0xABCDEFFF;
    op_0x00E0_clear_screen(&chip8);
    uint32_t actual = chip8.gfxbuffer[0];
    uint32_t expected = 0;
    TEST_ASSERT(actual == expected);
}

void test_op_0x1NNN(void) {
    struct chip8_t chip8;
    chip8_initialize(&chip8);
    uint16_t nnn = 0xABC;
    op_0x1NNN_jump(&chip8, nnn);
    uint16_t actual = chip8.pc;
    uint16_t expected = nnn;
    TEST_ASSERT(actual == expected);
}

void test_op_0x6XNN(void) {
    struct chip8_t chip8;
    chip8_initialize(&chip8);
    uint8_t x  = 0x5;
    uint8_t nn = 0xEE;
    op_0x6XNN_set_register(&chip8, x, nn);
    uint8_t actual = chip8.V[x];
    uint8_t expected = nn;
    TEST_ASSERT(actual == expected);
}

void test_op_0x7XNN(void) {
    struct chip8_t chip8;

    // Case 1: No overflow
    chip8_initialize(&chip8);
    uint8_t x  = 0x5;
    uint8_t nn = 0xEE;
    chip8.V[x] = 0x01;
    chip8.V[0xF] = 0;
    op_0x7XNN_add(&chip8, x, nn);
    TEST_ASSERT(chip8.V[x] == 0xEF);
    TEST_ASSERT(chip8.V[0xF] == 0);

    // Case 2: Overflow. Carry flag is NOT CHANGED
    chip8_initialize(&chip8);
    x  = 0x5;
    nn = 0xFF;
    chip8.V[x] = 0x05;
    chip8.V[0xF] = 0;
    op_0x7XNN_add(&chip8, x, nn); // Should overflow to 0x04
    TEST_ASSERT(chip8.V[x] == 0x04);
    TEST_ASSERT(chip8.V[0xF] == 0); // Carry flag should not be set
}

TEST_LIST = {
    { "00E0: Clear screen", test_op_00E0 },
    { "1NNN: Jump to address", test_op_0x1NNN },
    { "6XNN: Set register VX to NN", test_op_0x6XNN },
    { "7XNN: Add NN to register VX", test_op_0x7XNN },
    { NULL, NULL }
};
