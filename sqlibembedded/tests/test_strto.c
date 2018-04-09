#include "minunit.h"
#include "test_strto.h"
#include <sqstdlib.h>

static const char strstol_test_dec[] = "123";
static const char strstol_test_decpostjunk[] = "89771  junkystuff";
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

MU_TEST(test_sqstrstol_positivedecimal) 
{
    mu_assert_int_eq(123, sqstrstol(strstol_test_dec));
}

MU_TEST(test_sqstrstol_positivedecimal_junk) 
{
    mu_assert_int_eq(89771, sqstrstol(strstol_test_decpostjunk));
}

MU_TEST(test_sqstrstol_negativedecimal)
{
    mu_assert_int_eq(-8944, sqstrstol(strstol_test_negdec));
} 

MU_TEST(test_sqstrstol_positivedecimal_spaces) 
{
    mu_assert_int_eq(245, sqstrstol(strstol_test_spacedec));
}

MU_TEST(test_sqstrstol_hex) 
{
    mu_assert_int_eq(0xdEaDf00D, sqstrstol(strstol_test_hex));
}

MU_TEST(test_sqstrstol_hex_spaces) 
{  
    mu_assert_int_eq(0x155Ab87, sqstrstol(strstol_test_spacehex));
}

MU_TEST_SUITE(test_strto) 
{
    MU_SUITE_CONFIGURE(&test_strto_setup, &test_strto_teardown);
    MU_RUN_TEST(test_sqstrstol_positivedecimal);
    MU_RUN_TEST(test_sqstrstol_positivedecimal_junk);
    MU_RUN_TEST(test_sqstrstol_negativedecimal);
    MU_RUN_TEST(test_sqstrstol_positivedecimal_spaces);
    MU_RUN_TEST(test_sqstrstol_hex);
    MU_RUN_TEST(test_sqstrstol_hex_spaces);
}

int testStrtoSuite()
{
    MU_RUN_SUITE(test_strto);
    MU_REPORT();
    return minunit_fail;
}