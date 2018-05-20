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

char * mockStdoutGets(char * restrict s, int num)
{
    char * current = s;
    if ( num == 0 )
    {
        return NULL;
    }
    if ( num == 1 )
    {
        *current = '\0';
        return s;
    }
    // always keep one space free for the zero terminte
    int size = num - 1;
    while(size > 0)
    {
        uint8_t c;
        result r = stdoutQueueDequeue(&c);
        if(r == queueEmpty)
        {
            // no more characters
            *current = '\0';
            return s;
        }
        // TODO interpreting special characters
        switch(c)
        {
            case '\b':
                if(current > s)
                {
                    --current;
                    *current = '\0';    
                    ++size;
                }
            break;
            // lets handle \n and \r as terminators
            case '\n':
            case '\r':
                // terminate string and exit
                *current = c;
                ++current;
                --size;
                // we can always terminate as we keep one char free
                *current = '\0';
                return s;
            break;
            default:
                *current = c;
                ++current;
                --size;
            break;
        }
    }
    *current = '\0';
    return s;
}