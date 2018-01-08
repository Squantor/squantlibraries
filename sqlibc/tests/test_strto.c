#include "minunit.h"
#include "test_strto.h"
#include <sqstdlib.h>

static const char strstol_test_dec[] = "123";
static const char strstol_test_negdec[] = "-8944";
static const char strstol_test_spacedec[] = " \t245";
static const char strstol_test_hex[] = "0xdEaDf00D";
static const char strstol_test_spacehex[] = "  0x155Ab87";

void test_strto_setup(void) 
{
    
}

void test_strto_teardown(void) 
{

}

MU_TEST(test_sqstrstol_decimal) 
{
    mu_assert_int_eq(123, sqstrstol(strstol_test_dec));
    mu_assert_int_eq(-8944, sqstrstol(strstol_test_negdec));
    mu_assert_int_eq(245, sqstrstol(strstol_test_spacedec));
    mu_assert_int_eq(0xdEaDf00D, sqstrstol(strstol_test_hex));
    mu_assert_int_eq(0x155Ab87, sqstrstol(strstol_test_spacehex));
}

MU_TEST_SUITE_GLOBAL(test_strto) 
{
    MU_SUITE_CONFIGURE(&test_strto_setup, &test_strto_teardown);
    MU_RUN_TEST(test_sqstrstol_decimal);
}