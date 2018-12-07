#include <stddef.h>
#include <mock_stdio.h>
#include <mock_setup.h>
#include <queue_macro.h>

TEMPLATE_QUEUE_PROTO(stdinQueue, char)
TEMPLATE_QUEUE_VARS(stdinQueue, char, STDIOMOCK_BUFSIZE)
TEMPLATE_QUEUE_FUNCTIONS(stdinQueue, char, STDIOMOCK_BUFSIZE, (STDIOMOCK_BUFSIZE-1))

TEMPLATE_QUEUE_PROTO(stdoutQueue, char)
TEMPLATE_QUEUE_VARS(stdoutQueue, char, STDIOMOCK_BUFSIZE)
TEMPLATE_QUEUE_FUNCTIONS(stdoutQueue, char, STDIOMOCK_BUFSIZE, (STDIOMOCK_BUFSIZE-1))

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

result mockStdinWrite(char c)
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
    return noError;
}

result mockStdinRead(char *c)
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

result mockStdoutWrite(char c)
{
    return stdoutQueueEnqueue(&c);
}

result mockStdoutRead(char *c)
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
        char c;
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

/*
 * Keep reading Stdout until nothing is left.
 * Perfect for resetting stdout to empty state.
 */
void mockStdoutClear(void)
{
    char c;
    result r = stdoutQueueDequeue(&c);
    while(r != queueEmpty)
        r = stdoutQueueDequeue(&c);
}