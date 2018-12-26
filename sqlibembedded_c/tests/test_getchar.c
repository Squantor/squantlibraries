#include <stdbool.h>
#include <minunit.h>
#include <test_getchar.h>
#include <sqstdio.h>
#include <results.h>
#include <mock_stdio.h>

void test_getchar_setup(void) 
{
   mockStdinReset();
}

void test_getchar_teardown(void) 
{

}

MU_TEST(test_getchar_EOF) 
{
    mu_assert_int_eq(EOF, sqgetchar());
}

MU_TEST(test_getchar_normal) 
{
    mockStdinWrite('a');
    mu_assert_int_eq('a', sqgetchar());
}

MU_TEST_SUITE(test_getchar) 
{
    MU_SUITE_CONFIGURE(&test_getchar_setup, &test_getchar_teardown);
    MU_RUN_TEST(test_getchar_EOF);
    MU_RUN_TEST(test_getchar_normal);
}

int testGetcharSuite()
{
    MU_RUN_SUITE(test_getchar);
    MU_REPORT();
    return minunit_fail;
}