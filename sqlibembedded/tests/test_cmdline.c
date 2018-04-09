#include <stdbool.h>
#include <minunit.h>
#include <test_cmdline.h>
#include <results.h>
#include <mock_stdio.h>
#include <cmdline_commands.h>

void testCmdlineSetup(void) 
{
   mockStdinReset();
   mockStdoutReset();
}

void testCmdlineTeardown(void) 
{

}

MU_TEST(testCmdlineEmpty) 
{
    do {
        cmdlineProcess(cmdLineEntries);
    } while(mockStdinStatus() == queueNotEmpty);
    mu_assert_int_eq(queueEmpty, mockStdoutStatus());
}

MU_TEST_SUITE(testCmdline) 
{
    MU_SUITE_CONFIGURE(&testCmdlineSetup, &testCmdlineTeardown);
    MU_RUN_TEST(testCmdlineEmpty);
}

int testCmdlineSuite()
{
    MU_RUN_SUITE(testCmdline);
    MU_REPORT();
    return minunit_fail;
}