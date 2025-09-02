#include "acutest.h"
#include "core/chip8.h"
#include "core/opcodes.h"

void test_op_0x6XNN_unit(void) {
    struct chip8_t chip8;
    chip8_initialize(&chip8);
    uint8_t x  = 0x5;
    uint8_t nn = 0xEE;
    op_0x6XNN_set_register(&chip8, x, nn);
    uint8_t actual = chip8.V[x];
    uint8_t expected = nn;
    TEST_ASSERT(actual == expected);
}

TEST_LIST = {
    { "6XNN: Set register VX to NN", test_op_0x6XNN_unit},
    { NULL, NULL }
};
