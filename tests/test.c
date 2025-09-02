#include "acutest.h"
#include "core/chip8.h"

void test_pass(void) {
    struct chip8_t chip8;
    chip8_initialize(&chip8);
    chip8.memory[0] = 1;
    TEST_CHECK(chip8.memory[0] == 1);
}

void test_fail(void) {
    struct chip8_t chip8;
    chip8_initialize(&chip8);
    chip8.memory[0] = 0;
    TEST_CHECK(chip8.memory[0] == 1);
}

TEST_LIST = {
    { "pass", test_pass },
    { "fail", test_fail },
    { NULL, NULL }
};
