#include <mock_stdio.h>
#include <mock_setup.h>
#include <queue_macro.h>

TEMPLATE_QUEUE_PROTO(stdinQueue, uint8_t)
TEMPLATE_QUEUE_VARS(stdinQueue, uint8_t, STDIOMOCK_BUFSIZE)
TEMPLATE_QUEUE_FUNCTIONS(stdinQueue, uint8_t, STDIOMOCK_BUFSIZE, (STDIOMOCK_BUFSIZE-1))

TEMPLATE_QUEUE_PROTO(stdoutQueue, uint8_t)
TEMPLATE_QUEUE_VARS(stdoutQueue, uint8_t, STDIOMOCK_BUFSIZE)
TEMPLATE_QUEUE_FUNCTIONS(stdoutQueue, uint8_t, STDIOMOCK_BUFSIZE, (STDIOMOCK_BUFSIZE-1))

result mockStdioSetup()
{
    // setup ringbuffers for stdin and stdout
    stdinQueueInit();
    stdoutQueueInit();
    return noError;
}

// reset stdin to empty
void mockStdinReset()
{
    stdinQueueInit();
}

result mockStdinStatus()
{
    return stdinQueueState();
}

result mockStdinWrite(uint8_t c)
{
    return stdinQueueEnqueue(&c);
}

result mockStdinRead(uint8_t *c)
{
    stdinQueueDequeue(c);
    return noError;
}

void mockStdoutReset()
{
    stdoutQueueInit();
}

result mockStdoutStatus()
{
    return stdoutQueueState();
}

result mockStdoutWrite(uint8_t c)
{
    return stdoutQueueEnqueue(&c);
}

result mockStdoutRead(uint8_t *c)
{
    return stdoutQueueDequeue(c);
}