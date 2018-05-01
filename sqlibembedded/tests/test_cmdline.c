#include <minunit.h>
#include <stdbool.h>
#include <stdio.h>
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
   cmdlineInit();
}

void testCmdlineTeardown(void) 
{

}

MU_TEST(testCmdlineEmpty) 
{
    mu_check(4 == testCmdlineLoop(5));
    mu_check(queueEmpty == mockStdoutStatus());
}

MU_TEST(testCmdlineCrLf) 
{
    char cmdline[16];
    mu_check(noError == mockStdinPuts("\r"));
    mu_check(9 == testCmdlineLoop(10));
    mu_check(mockStdoutGetsbuf(cmdline, sizeof(cmdline), strlen("\r")) != NULL);
    mu_check(strcmp(cmdline, "\r") == 0);
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST(testCmdlineHelp) 
{
    char helpcmd[32];
    char helpline1[32];
    char helpline2[32];
    mu_check(noError == mockStdinPuts("help\r"));
    mu_check(5 == testCmdlineLoop(10));
    mu_check(mockStdoutGetsbuf(helpcmd, sizeof(helpcmd), strlen("help\r")) != NULL);
    mu_check(mockStdoutGetsbuf(helpline1, sizeof(helpcmd), strlen("test\n")) != NULL);
    mu_check(mockStdoutGetsbuf(helpline2, sizeof(helpcmd), strlen("help\n")) != NULL);
    mu_check(strcmp(helpcmd, "help\r") == 0);
    mu_check(strcmp(helpline1, "test\n") == 0);
    mu_check(strcmp(helpline2, "help\n") == 0);
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST(testCmdlineHelpBuffer) 
{
    char helpcmd[32];
    char helpline1[32];
    char helpline2[32];
    // redo test a few times to let the buffer overflow
    for(int i = 0; i < 20; i++)
    {
        mu_check(noError == mockStdinPuts("help\r"));
        mu_check(5 == testCmdlineLoop(10));
        mu_check(mockStdoutGetsbuf(helpcmd, sizeof(helpcmd), strlen("help\r")) != NULL);
        mu_check(mockStdoutGetsbuf(helpline1, sizeof(helpcmd), strlen("test\n")) != NULL);
        mu_check(mockStdoutGetsbuf(helpline2, sizeof(helpcmd), strlen("help\n")) != NULL);
        mu_check(strcmp(helpcmd, "help\r") == 0);
        mu_check(strcmp(helpline1, "test\n") == 0);
        mu_check(strcmp(helpline2, "help\n") == 0);
        mu_check(queueEmpty == mockStdoutStatus()); 
    }
}

MU_TEST(testCmdlineArgs) 
{
    char cmdline[16];
    char cmdoutput[64];
    mu_check(noError == mockStdinPuts("test 51 99\r"));
    mu_check(4 == testCmdlineLoop(15));
    mu_check(mockStdoutGetsbuf(cmdline, sizeof(cmdline), strlen("test 51 99\r")) != NULL);
    mu_check(mockStdoutGetsbuf(cmdoutput, sizeof(cmdoutput), strlen("Hello World! 00051 00099\n")) != NULL);
    mu_check(strcmp(cmdline, "test 51 99\r") == 0);
    mu_check(strcmp(cmdoutput, "Hello World! 00051 00099\n") == 0);
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST(testCmdlinePreviousEmpty) 
{
    char cmdline[16];
    char cmdoutput[64];
   
    // emit the up button escape sequence
    mu_check(noError == mockStdinPuts("\e[A"));
    mu_check(12 == testCmdlineLoop(15));
    // check if we do not get previous command
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST(testCmdlinePrevious) 
{
    char cmdline[16];
    char cmdoutput[64];
    mu_check(noError == mockStdinPuts("test 51 99\r"));
    mu_check(4 == testCmdlineLoop(15));
    mu_check(mockStdoutGetsbuf(cmdline, sizeof(cmdline), strlen("test 51 99\r")) != NULL);
    mu_check(mockStdoutGetsbuf(cmdoutput, sizeof(cmdoutput), strlen("Hello World! 00051 00099\n")) != NULL);
   
    // emit the up button escape sequence
    mu_check(noError == mockStdinPuts("\e[A"));
    mu_check(12 == testCmdlineLoop(15));
    // check if we get previous command
    mu_check(mockStdoutGetsbuf(cmdline, sizeof(cmdline), strlen("test 51 99\r")) != NULL);
    mu_check(strcmp(cmdline, "test 51 99\r") == 0);
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST_SUITE(testCmdline) 
{
    MU_SUITE_CONFIGURE(&testCmdlineSetup, &testCmdlineTeardown);
    MU_RUN_TEST(testCmdlineEmpty);
    MU_RUN_TEST(testCmdlineCrLf);
    MU_RUN_TEST(testCmdlineHelp);
    MU_RUN_TEST(testCmdlineHelpBuffer);
    MU_RUN_TEST(testCmdlineArgs);
    //MU_RUN_TEST(testCmdlinePreviousEmpty);
    //MU_RUN_TEST(testCmdlinePrevious);
}

int testCmdlineSuite()
{
    MU_RUN_SUITE(testCmdline);
    MU_REPORT();
    return minunit_fail;
}