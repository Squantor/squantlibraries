#include <stdbool.h>
#include <minunit.h>
#include <sqstdio.h>
#include <test_cmdline.h>
#include <results.h>
#include <mock_stdio.h>
#include <cmdline_commands.h>

int testCmdlineLoop(int timeout)
{
    int counts = timeout;
    do {
        cmdlineProcess(cmdLineEntries);
        counts--;
    } while(mockStdinStatus() == queueNotEmpty && (counts > 0));
    return counts;
}

void testCmdlineSetup(void) 
{
   mockStdinReset();
   mockStdoutReset();
}

void testCmdlineTeardown(void) 
{

}

MU_TEST(testCmdlineCrLf) 
{
    mu_check(noError == mockStdinPuts("\r"));
    mu_check(9 == testCmdlineLoop(10));
    mu_assert_int_eq(queueEmpty, mockStdinStatus()); 
}

MU_TEST(testCmdlineEmpty) 
{
    mu_check(4 == testCmdlineLoop(5));
    mu_check(queueEmpty == mockStdinStatus());
}

MU_TEST(testCmdlineHelp) 
{

}

MU_TEST(testCmdlineTest) 
{

}

MU_TEST(testCmdlineArgs) 
{

}

MU_TEST_SUITE(testCmdline) 
{
    MU_SUITE_CONFIGURE(&testCmdlineSetup, &testCmdlineTeardown);
    MU_RUN_TEST(testCmdlineEmpty);
    MU_RUN_TEST(testCmdlineCrLf);
    MU_RUN_TEST(testCmdlineHelp);
    MU_RUN_TEST(testCmdlineTest);
    MU_RUN_TEST(testCmdlineArgs);
}

int testCmdlineSuite()
{
    MU_RUN_SUITE(testCmdline);
    MU_REPORT();
    return minunit_fail;
}