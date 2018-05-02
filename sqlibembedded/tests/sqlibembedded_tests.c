#include <stdio.h>
#include <mock_stdio.h>
#include <test_strlen.h>
#include <test_strto.h>
#include <test_strtok.h>
#include <test_putchar.h>
#include <test_getchar.h>
#include <test_cmdline.h>
#include <test_parse_ansi.h>


int main(int argc, char *argv[]) 
{
    mockStdioSetup();
    int failedTests = 0;
    failedTests += testStrlenSuite();
    failedTests += testStrtoSuite();
    failedTests += testStrtokSuite();
    failedTests += testPutcharSuite();
    failedTests += testGetcharSuite();
    failedTests += testCmdlineSuite();
    failedTests += testParseAnsiSuite();
    if(failedTests > 0)
    {
        printf("ERROR: %d tests failed\n", failedTests);
        return -1;
    }
    else
    {
        printf("All tests ran succesfully\n");
        return 0;
    }
}

