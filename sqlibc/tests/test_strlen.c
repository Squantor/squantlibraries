#include "minunit.h"
#include "test_strlen.h"
#include <sqstring.h>

static const char* strlen_test_length = "TestString";

void test_strlen_setup(void) 
{
    
}

void test_strlen_teardown(void) 
{

}

MU_TEST(test_strlen_normal) {
	mu_assert_int_eq(4, sqstrlen(strlen_test_length));
}


MU_TEST_SUITE_GLOBAL(test_strlen) 
{
    MU_SUITE_CONFIGURE(&test_strlen_setup, &test_strlen_teardown);
    
    MU_RUN_TEST(test_strlen_normal);
}