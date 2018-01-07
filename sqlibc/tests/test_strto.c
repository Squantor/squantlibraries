#include "minunit.h"
#include "test_strto.h"
#include <sqstdlib.h>

static const char strlen_test_length[] = "123";

void test_strto_setup(void) 
{
    
}

void test_strto_teardown(void) 
{

}

MU_TEST(test_strtol_decimal) 
{
    
}

MU_TEST_SUITE_GLOBAL(test_strto) 
{
    MU_SUITE_CONFIGURE(&test_strto_setup, &test_strto_teardown);
}