#include <minunit.h>
#include <test_queue_string.h>
#include <results.h>

void testSetupQueueString(void) 
{

    }

void testTeardownQueueString(void) 
{

}

MU_TEST(testEnqueue) 
{

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