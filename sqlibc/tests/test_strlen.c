#include "minunit.h"
#include "test_strlen.h"
#include <sqstring.h>

static const char strlen_test_length[] = "TestString";
static const char strlen_test_empty[] = "";
static const char strnlen_test_invalid[5] = {'a', 'b', 'c', 'd', 'e' };

void test_strlen_setup(void) 
{
    
}

void test_strlen_teardown(void) 
{

}

MU_TEST(test_strlen_normal) 
{
    mu_assert_int_eq(10, sqstrlen(strlen_test_length));
}

MU_TEST(test_strlen_empty) 
{
    mu_assert_int_eq(0, sqstrlen(strlen_test_empty));
}

MU_TEST(test_strnlen_normal) 
{
    mu_assert_int_eq(10, sqstrnlen(strlen_test_length, sizeof(strlen_test_length)));
}

MU_TEST(test_strnlen_empty) 
{
    mu_assert_int_eq(0, sqstrnlen(strlen_test_empty, sizeof(strlen_test_empty)));
}

MU_TEST(test_strnlen_invalid) 
{
    mu_assert_int_eq(0, sqstrnlen(strnlen_test_invalid, sizeof(strnlen_test_invalid)));
}

MU_TEST_SUITE_GLOBAL(test_strlen) 
{
    MU_SUITE_CONFIGURE(&test_strlen_setup, &test_strlen_teardown);
    
    MU_RUN_TEST(test_strlen_normal);
    MU_RUN_TEST(test_strlen_empty);
    MU_RUN_TEST(test_strnlen_normal);
    MU_RUN_TEST(test_strnlen_empty);
    MU_RUN_TEST(test_strnlen_invalid);
}

void testStrlenSuite()
{
    MU_RUN_SUITE(test_strlen);
    MU_REPORT();
}