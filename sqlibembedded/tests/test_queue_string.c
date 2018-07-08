#include <minunit.h>
#include <string.h>
#include <results.h>
#include <queue_string.h>
#include <test_queue_string.h>

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
    // add empty string
    // add too big string
    // add string
    // add so many strings you overflow the buffer
}

MU_TEST(testDequeue) 
{

}


MU_TEST(testEnqueueDequeue) 
{

}

MU_TEST(testEnqueueDequeueOverwrite) 
{

}


MU_TEST_SUITE(test_getchar) 
{
    MU_SUITE_CONFIGURE(&testSetupQueueString, &testTeardownQueueString);
    MU_RUN_TEST(testEnqueue);
    MU_RUN_TEST(testDequeue);
    MU_RUN_TEST(testEnqueueDequeue);
    MU_RUN_TEST(testEnqueueDequeueOverwrite);
}

int testQueueString()
{
    MU_RUN_SUITE(test_getchar);
    MU_REPORT();
    return minunit_fail;
}