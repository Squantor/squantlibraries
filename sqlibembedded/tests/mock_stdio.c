#include <mock_stdio.h>
#include <mock_setup.h>
#include <queue_compact.h>

struct
{
    uint32_t    mask;
    uint32_t    head;
    uint32_t    tail;
    void *      data[STDIOMOCK_BUFSIZE];
} queueStdin;

struct
{
    uint32_t    mask;
    uint32_t    head;
    uint32_t    tail;
    void *      data[STDIOMOCK_BUFSIZE];
} queueStdout;


result mockStdioSetup()
{
    // setup ringbuffers for stdin and stdout
    queueInit(&queueStdin, STDIOMOCK_BUFSIZE-1);
    queueInit(&queueStdout, STDIOMOCK_BUFSIZE-1);
    return noError;
}

// reset stdin to empty
void mockStdinReset()
{
    queueStdin.head = queueStdin.tail = 0;
}

result mockStdinStatus()
{
    return queueFillStatus(&queueStdin);
}

result mockStdinWrite(uint8_t c)
{
    queueEnqueue(&queueStdin, &c);
    return noError;
}

result mockStdinRead(uint8_t *c)
{
    queueDequeue(&queueStdin, c);
    return noError;
}

void mockStdoutReset()
{
    queueStdout.head = queueStdout.tail = 0;
}

result mockStdoutStatus()
{
    return queueFillStatus(&queueStdout);
}

result mockStdoutWrite(uint8_t c)
{
    queueEnqueue(&queueStdout, &c);
    return noError;
}

result mockStdoutRead(uint8_t *c)
{
    queueDequeue(&queueStdout, c);
    return noError;
}