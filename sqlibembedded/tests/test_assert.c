#include "minunit.h"
#include "test_assert.h"
#include <assert.h>

void test_assert_setup(void) 
{
    
}

void test_assert_teardown(void) 
{

}

MU_TEST(test_assert_debug) 
{
    
}

MU_TEST(test_assert_release) 
{
    
}

MU_TEST_SUITE(test_assert) 
{
    MU_SUITE_CONFIGURE(&test_assert_setup, &test_assert_teardown);
    MU_RUN_TEST(test_assert_debug);
    MU_RUN_TEST(test_assert_release);
}

int testAssertSuite()
{
    MU_RUN_SUITE(test_assert);
    MU_REPORT();
    return minunit_fail;
}