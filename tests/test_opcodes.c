#include "core/chip8.h"
#include "core/opcodes.h"
#include "core/errors.h"
#include <stdlib.h>
#include <check.h>

// 0x1NNN tests
START_TEST(test_op_0x1NNN_jump_valid)
{
    struct chip8_t chip8;
    init_chip8(&chip8);
    // Example: Jump to address 0x300
    uint16_t address = 0x0300;
    int err = op_0x1NNN_jump(&chip8, address);
    ck_assert_int_eq(err, 0);
    ck_assert_int_eq(chip8.program_counter, 0x300);
}
END_TEST
START_TEST(test_op_0x1NNN_jump_invalid_low)
{
    struct chip8_t chip8;
    init_chip8(&chip8);
    // Example: Invalid jump to address below 0x200
    uint16_t address = 0x0100;
    int err = op_0x1NNN_jump(&chip8, address);
    ck_assert_int_eq(err, -EC8_FAULT);
    ck_assert_int_eq(chip8.program_counter, 0x200); // Shouldn't change
}
END_TEST
START_TEST(test_op_0x1NNN_jump_invalid_high)
{
    struct chip8_t chip8;
    init_chip8(&chip8);
    // Example: Invalid jump to address above 0xFFF
    uint16_t address = 0x1000;
    int err = op_0x1NNN_jump(&chip8, address);
    ck_assert_int_eq(err, -EC8_FAULT);
    ck_assert_int_eq(chip8.program_counter, 0x200); // Shouldn't change
}
END_TEST

// 0x6XNN tests
START_TEST(test_op_0x6XNN_set)
{
    struct chip8_t chip8;
    uint8_t register_index = 0;
    init_chip8(&chip8);
    uint8_t value = 0xAB;
    int err = op_0x6XNN_set(&chip8, register_index, value);
    ck_assert_int_eq(err, 0);
    ck_assert_int_eq(chip8.v_registers[register_index], value);
}
END_TEST

// 0x7XNN tests
START_TEST(test_op_0x7XNN_add_nooverflow)
{
    struct chip8_t chip8;
    uint8_t register_index = 0;
    init_chip8(&chip8);
    chip8.v_registers[register_index] = 0x10;
    uint8_t value = 0x20;
    uint8_t expected = 0x30;
    int err = op_0x7XNN_add(&chip8, register_index, value);
    ck_assert_int_eq(err, 0);
    ck_assert_int_eq(chip8.v_registers[register_index], expected);
}
END_TEST
START_TEST(test_op_0x7XNN_add_overflow)
{
    struct chip8_t chip8;
    init_chip8(&chip8);
    
    uint8_t register_index = 0;
    uint8_t flag_index = 0xF;
    uint8_t flag = chip8.v_registers[flag_index];
    chip8.v_registers[register_index] = 0xFF;
    uint8_t value = 0x01;
    uint8_t expected = 0x00; // Wrap around on overflow
    int err = op_0x7XNN_add(&chip8, register_index, value);
    ck_assert_int_eq(err, 0);
    ck_assert_int_eq(chip8.v_registers[register_index], expected);
    // Overflow should not affect VF
    ck_assert_int_eq(chip8.v_registers[flag_index], flag);
}
END_TEST

// 0x8XY0 tests
START_TEST(test_op_0x8XY0_load)
{
    struct chip8_t chip8;
    init_chip8(&chip8);
    uint8_t reg_x = 0x1;
    uint8_t reg_y = 0x2;
    chip8.v_registers[reg_y] = 0xAB;
    int err = op_0x8XY0_load(&chip8, reg_x, reg_y);
    ck_assert_int_eq(err, 0);
    ck_assert_int_eq(chip8.v_registers[reg_x], 0xAB);
    // VY shouldn't change
    ck_assert_int_eq(chip8.v_registers[reg_y], 0xAB);
}


int main(void)
{
    Suite *s = suite_create("Chip8 Opcodes");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_op_0x1NNN_jump_valid);
    tcase_add_test(tc_core, test_op_0x1NNN_jump_invalid_low);
    tcase_add_test(tc_core, test_op_0x1NNN_jump_invalid_high);

    tcase_add_test(tc_core, test_op_0x6XNN_set);
    
    tcase_add_test(tc_core, test_op_0x7XNN_add_nooverflow);
    tcase_add_test(tc_core, test_op_0x7XNN_add_overflow);

    tcase_add_test(tc_core, test_op_0x8XY0_load);
    suite_add_tcase(s, tc_core);

    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
