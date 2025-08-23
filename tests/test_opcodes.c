#include "core/chip8.h"
#include "core/opcodes.h"
#include "core/errors.h"
#include <stdlib.h>
#include <check.h>


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
    // Example: Jump to address 0x300
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
    // Example: Jump to address 0x300
    uint16_t address = 0x1000;
    int err = op_0x1NNN_jump(&chip8, address);
    ck_assert_int_eq(err, -EC8_FAULT);
    ck_assert_int_eq(chip8.program_counter, 0x200); // Shouldn't change
}
END_TEST


int main(void)
{
    Suite *s = suite_create("Chip8 Opcodes");
    TCase *tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_op_0x1NNN_jump_valid);
    tcase_add_test(tc_core, test_op_0x1NNN_jump_invalid_low);
    tcase_add_test(tc_core, test_op_0x1NNN_jump_invalid_high);
    suite_add_tcase(s, tc_core);

    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);
    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
