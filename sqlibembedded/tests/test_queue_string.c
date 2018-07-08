#include <minunit.h>
#include <string.h>
#include <results.h>
#include <queue_string.h>
#include <test_queue_string.h>
#include <sqstring.h>

char testQueueStringBuffer[128];
t_queueString testQueue = {.mask = sizeof(testQueueStringBuffer)-1, .head = 0, .tail = 0, .data = testQueueStringBuffer};

void testSetupQueueString(void) 
{
    // clear queue
    testQueue.head = 0;
    testQueue.tail = 0;
    memset(testQueueStringBuffer, 0, sizeof(testQueueStringBuffer));
}

void testTeardownQueueString(void) 
{

}

MU_TEST(testEnqueue) 
{
    mu_check(queueStringEnqueue(NULL, NULL) == invalidArg);
    mu_check(queueStringEnqueue(&testQueue, NULL) == invalidArg);
    
    char *stringEmpty = "";
    char stringMassive[128+20];
    char *stringNormal = "Hello World\n";
    char stringNumeric[16];
    memset(stringMassive, 'a', sizeof(stringMassive)-1);
    // zero terminate massive string
    stringMassive[sizeof(stringMassive)-1] = 0;
    // add empty string
    mu_check(queueStringEnqueue(&testQueue, stringEmpty) == dataInvalid);
    // add too big string
    mu_check(queueStringEnqueue(&testQueue, stringMassive) == dataInvalid);
    // add string
    mu_check(queueStringEnqueue(&testQueue, stringNormal) == noError);
    // add so many strings you overflow the buffer a few times
    for(int i = 0; i < 200; i++)
    {
        sprintf(stringNumeric,"%d",i);
        mu_check(queueStringEnqueue(&testQueue, stringNumeric) == noError);
    }
}

MU_TEST(testDequeue) 
{
    mu_check(queueStringDequeue(NULL, NULL) == invalidArg);
    mu_check(queueStringDequeue(&testQueue, NULL) == invalidArg);
}


MU_TEST(testEnqueueDequeue) 
{
    char stringInput[] = "Hello World\n";
    char stringOutput[32];
    mu_check(queueStringEnqueue(&testQueue, stringInput) == noError);
    mu_check(queueStringDequeue(&testQueue, stringOutput) == noError);
    mu_check(strcmp(stringInput, stringOutput) == 0);
}

MU_TEST(testEnqueueDequeueOverwrite) 
{
    char stringNumeric[16];
    char stringOutput[32];
    // add so many strings you overflow the buffer a few times
    for(int i = 0; i < 200; i++)
    {
        sprintf(stringNumeric,"%d",i);
        mu_check(queueStringEnqueue(&testQueue, stringNumeric) == noError);
    }
    
    for(int i = 150; i < 200; i++)
    {
        sprintf(stringNumeric,"%d",i);
        mu_check(queueStringDequeue(&testQueue, stringOutput) == noError);
        mu_check(strcmp(stringNumeric, stringOutput) == 0); 
    }
}


MU_TEST_SUITE(testSuiteQueueString) 
{
    MU_SUITE_CONFIGURE(&testSetupQueueString, &testTeardownQueueString);
    MU_RUN_TEST(testEnqueue);
    MU_RUN_TEST(testDequeue);
    MU_RUN_TEST(testEnqueueDequeue);
    MU_RUN_TEST(testEnqueueDequeueOverwrite);
    // TODO a test that checks if the tail overtake does not match end of buffer garbage
}

int testQueueString()
{
    MU_RUN_SUITE(testSuiteQueueString);
    MU_REPORT();
    return minunit_fail;
}