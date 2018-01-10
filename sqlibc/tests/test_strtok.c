#include "minunit.h"
#include "test_strtok.h"
#include <sqstring.h>

void test_strtok_setup(void) 
{
    
}

void test_strtok_teardown(void) 
{

}

MU_TEST(test_sqstrstok) 
{

}

MU_TEST(test_sqstrstoks) 
{

}


MU_TEST_SUITE_GLOBAL(test_strtok) 
{
    MU_SUITE_CONFIGURE(&test_strtok_setup, &test_strtok_teardown);
    MU_RUN_TEST(test_sqstrstok);
    MU_RUN_TEST(test_sqstrstoks);
}
