#include <stdbool.h>
#include "minunit.h"
#include "test_cmdline.h"
#include <results.h>

void testCmdlineSetup(void) 
{
   
}

void testCmdlineTeardown(void) 
{

}

MU_TEST(testCmdlineEmpty) 
{

}

MU_TEST_SUITE(testCmdline) 
{
    MU_SUITE_CONFIGURE(&testCmdlineSetup, &testCmdlineTeardown);
}

int testCmdlineSuite()
{
    MU_RUN_SUITE(testCmdline);
    MU_REPORT();
    return minunit_fail;
}