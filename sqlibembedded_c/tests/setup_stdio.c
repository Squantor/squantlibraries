/*
 * Standard stream definitions with their helper functions
 */
#include <sqstdlib.h>
#include <sqstdio.h>
#include <results.h>
#include <mock_stdio.h>

result stdinRead(char *c)
{
    if(mockStdinStatus() == queueNotEmpty)
    {
        mockStdinRead(c);
        return noError;
    }
    else
        return streamEOF;
}

const rStream sqstdindef = {
    stdinRead,
};

result stdoutWrite(char c)
{
    if(mockStdoutStatus() == queueFull)
        return streamEOF;
    else
    {
        mockStdoutWrite(c);
        return noError;
    }
}

const wStream sqstdoutdef = {
    stdoutWrite,
};
