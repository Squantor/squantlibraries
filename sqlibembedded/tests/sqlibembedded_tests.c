#include "minunit.h"
#include "test_strlen.h"
#include "test_strto.h"
#include "test_strtok.h"
#include "test_putchar.h"
#include "test_getchar.h"


int main(int argc, char *argv[]) 
{
    int failedTests = 0;
    failedTests += testStrlenSuite();
    failedTests += testStrtoSuite();
    failedTests += testStrtokSuite();
    failedTests += testPutcharSuite();
    failedTests += testGetcharSuite();
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

