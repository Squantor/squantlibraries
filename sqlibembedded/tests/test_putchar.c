#include <stdbool.h>
#include <minunit.h>
#include <test_putchar.h>
#include <sqstdio.h>
#include <mock_stdio.h>

void test_putchar_setup(void) 
{
   mockStdoutReset();
}

void test_putchar_teardown(void) 
{

}

MU_TEST(test_putchar_EOF) 
{
    mu_assert_int_eq(EOF, sqputchar('a'));
}

MU_TEST(test_putchar_normal) 
{
    mu_assert_int_eq('a', sqputchar('a'));
    uint8_t c;
    mockStdoutRead(&c);
    mu_assert_int_eq('a', c);
}

MU_TEST_SUITE(test_putchar) 
{
    MU_SUITE_CONFIGURE(&test_putchar_setup, &test_putchar_teardown);
    MU_RUN_TEST(test_putchar_EOF);
    MU_RUN_TEST(test_putchar_normal);
}

int testPutcharSuite()
{
    MU_RUN_SUITE(test_putchar);
    MU_REPORT();
    return minunit_fail;
}