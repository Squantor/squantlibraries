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
        promptProcess(cmdLineEntries);
        counts--;
    } while(mockStdinStatus() == queueNotEmpty && (counts > 0));
    return counts;
}

void testCmdlineSetup(void) 
{
   mockStdinReset();
   mockStdoutReset();
   promptInit();
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
    mu_check(mockStdoutGets(cmdline, sizeof(cmdline)) == cmdline);
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
    mu_check(mockStdoutGets(helpcmd, sizeof(helpcmd)) == helpcmd);
    mu_check(mockStdoutGets(helpline1, sizeof(helpcmd)) == helpline1);
    mu_check(mockStdoutGets(helpline2, sizeof(helpcmd)) == helpline2);
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
        mu_check(mockStdoutGets(helpcmd, sizeof(helpcmd)) == helpcmd);
        mu_check(mockStdoutGets(helpline1, sizeof(helpcmd)) == helpline1);
        mu_check(mockStdoutGets(helpline2, sizeof(helpcmd)) == helpline2);
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
    mu_check(mockStdoutGets(cmdline, sizeof(cmdline)) == cmdline);
    mu_check(mockStdoutGets(cmdoutput, sizeof(cmdoutput)) == cmdoutput);
    mu_check(strcmp(cmdline, "test 51 99\r") == 0);
    mu_check(strcmp(cmdoutput, "Hello World! 00051 00099\n") == 0);
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST(testCmdlineIgnoreEscapes)
{
    // emit an unknown escape sequence
    mu_check(noError == mockStdinPuts("\e_"));
    mu_check(13 == testCmdlineLoop(15));
    // check if stdout is empty
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST(testCmdlinePreviousEmpty) 
{  
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
    mockStdinPuts("test 51 99\r");
    testCmdlineLoop(15);
    mockStdoutGets(cmdline, sizeof(cmdline));
    mockStdoutGets(cmdoutput, sizeof(cmdoutput));
   
    // emit the up button escape sequence
    mu_check(noError == mockStdinPuts("\e[A"));
    mu_check(12 == testCmdlineLoop(15));
    // check if we get previous command
    mu_check(mockStdoutGets(cmdline, sizeof(cmdline)) == cmdline);
    mu_check(strcmp(cmdline, "test 51 99") == 0);
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST(testCmdlinePreviousNonEmptyPrompt) 
{
    char cmdline[16];
    mockStdinPuts("test 51 99\r");
    testCmdlineLoop(15);
    // input a something on the prompt, should get erased
    mockStdinPuts("foo");
    testCmdlineLoop(5);
    mockStdoutClear();
   
    // emit the up button escape sequence
    mu_check(noError == mockStdinPuts("\e[A"));
    mu_check(12 == testCmdlineLoop(15));
    // check if we get previous command
    mu_check(mockStdoutGets(cmdline, sizeof(cmdline)) == cmdline);
    mu_check(strcmp(cmdline, "test 51 99") == 0);
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST(testCmdlineMultiPrevious)
{
    char prompt[16];
    mockStdinPuts("test 51 99\r");
    testCmdlineLoop(15);
    // input a something on the prompt, should get erased
    mockStdinPuts("foo\r");
    testCmdlineLoop(5);
    mockStdoutClear();
   
    // emit the up button escape sequence, multiple times
    mu_check(noError == mockStdinPuts("\e[A"));
    mu_check(12 == testCmdlineLoop(15));
    mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
    mu_check(strcmp(prompt, "foo") == 0);

    mu_check(noError == mockStdinPuts("\e[A"));
    mu_check(12 == testCmdlineLoop(15));
    mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
    mu_check(strcmp(prompt, "test 51 99") == 0);    
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST(testCmdlinePreviousNext)
{
    char prompt[16];
    mockStdinPuts("test 51 99\r");
    testCmdlineLoop(15);
    // input a something on the prompt, should get erased
    mockStdinPuts("foo\r");
    testCmdlineLoop(5);
    mockStdoutClear();
   
    // emit the up button escape sequence, multiple times
    mu_check(noError == mockStdinPuts("\e[A"));
    mu_check(12 == testCmdlineLoop(15));
    mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
    mu_check(strcmp(prompt, "foo") == 0);

    mu_check(noError == mockStdinPuts("\e[A"));
    mu_check(12 == testCmdlineLoop(15));
    mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
    mu_check(strcmp(prompt, "test 51 99") == 0);  

    mu_check(noError == mockStdinPuts("\e[B"));
    mu_check(12 == testCmdlineLoop(15));
    mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
    mu_check(strcmp(prompt, "foo") == 0);
  
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST(testCmdlineMultiPreviousMultiNext)
{
    char prompt[16];
    mockStdinPuts("test 51 99\r");
    testCmdlineLoop(15);
    mockStdinPuts("foo\r");
    testCmdlineLoop(5);
    mockStdinPuts("bar\r");
    testCmdlineLoop(5);
    mockStdoutClear();
   
    // emit the up button escape sequence, multiple times
    mu_check(noError == mockStdinPuts("\e[A"));
    mu_check(12 == testCmdlineLoop(15));
    mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
    mu_check(strcmp(prompt, "bar") == 0);
    
    for(int i = 0; i < 10; i++)
    {
        mu_check(noError == mockStdinPuts("\e[A"));
        mu_check(12 == testCmdlineLoop(15));
        mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
        mu_check(strcmp(prompt, "foo") == 0);  

        mu_check(noError == mockStdinPuts("\e[B"));
        mu_check(12 == testCmdlineLoop(15));
        mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
        mu_check(strcmp(prompt, "bar") == 0);
        
    }
    mu_check(queueEmpty == mockStdoutStatus()); 
}

MU_TEST(testCmdlineMultiNextBufferExceed)
{
    char prompt[16];
    char teststring[32];
     
    // emit a bunch of commands to fill the history buffer up completely
    for(int i = 0; i < 20; i++)
    {
        sprintf(teststring, "blaat %d\r",i);
        mockStdinPuts(teststring);
        testCmdlineLoop(15);
    }
    mockStdoutClear();
    // check if we get what we expect
    for(int i = 19; i > 6; i--)
    {
        printf("%d \n",i);
        sprintf(teststring, "blaat %d",i);
        mu_check(noError == mockStdinPuts("\e[A"));
        mu_check(12 == testCmdlineLoop(15));
        mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
        mu_check(strcmp(prompt, teststring) == 0);
    }
    
    // reached end, should be no command left anymore
    mu_check(noError == mockStdinPuts("\e[A"));
    mu_check(12 == testCmdlineLoop(15));
    mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
    mu_check(strcmp(prompt, "") == 0);
    
    // press enter just to clear
    mockStdinPuts("\r");
    testCmdlineLoop(1);
    mockStdoutClear();
    
    // emit a bunch of commands to fill the history buffer up completely
    for(int i = 80; i < 100; i++)
    {
        sprintf(teststring, "blaat %d\r",i);
        mockStdinPuts(teststring);
        testCmdlineLoop(15);
    }
    
    // check if we get what we expect
    for(int i = 99; i > 78; i--)
    {
        printf("%d \n",i);
        sprintf(teststring, "blaat %d",i);
        mu_check(noError == mockStdinPuts("\e[A"));
        mu_check(12 == testCmdlineLoop(15));
        mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
        mu_check(strcmp(prompt, teststring) == 0);
    }
    
    // reached end, should be no command left anymore
    mu_check(noError == mockStdinPuts("\e[A"));
    mu_check(12 == testCmdlineLoop(15));
    mu_check(mockStdoutGets(prompt, sizeof(prompt)) == prompt);
    mu_check(strcmp(prompt, "") == 0);
    
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
    MU_RUN_TEST(testCmdlineIgnoreEscapes);
    MU_RUN_TEST(testCmdlinePreviousEmpty);
    MU_RUN_TEST(testCmdlinePrevious);
    MU_RUN_TEST(testCmdlinePreviousNonEmptyPrompt);
    MU_RUN_TEST(testCmdlineMultiPrevious);
    MU_RUN_TEST(testCmdlinePreviousNext);
    MU_RUN_TEST(testCmdlineMultiPreviousMultiNext);
    //MU_RUN_TEST(testCmdlineMultiNextBufferExceed);
}

int testCmdlineSuite()
{
    MU_RUN_SUITE(testCmdline);
    MU_REPORT();
    return minunit_fail;
}