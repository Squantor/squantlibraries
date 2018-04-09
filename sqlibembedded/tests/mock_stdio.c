#include <stddef.h>
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

result mockStdinPuts(char * s)
{
    while( *s != '\0' )
    {
        if( stdinQueueEnqueue( s ) != noError)
        {
            return error;
        }
        ++s;
    }
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

char * mockStdoutGetsbuf(char * restrict s, int size, int charcount)
{
    if ( size == 0 )
    {
        return NULL;
    }
    if ( size == 1 )
    {
        *s = '\0';
        return s;
    }
    size -= 1;
    while(size > 0)
    {
        uint8_t c;
        result r = stdoutQueueDequeue(&c);
        if(r == queueEmpty)
            return NULL;
        *s = c;
        ++s;
        --size;
        --charcount;
        if(charcount == 0)
        {
            *s = '\0';
            return s;
        }
    }
    *s = '\0';
    return s;
}