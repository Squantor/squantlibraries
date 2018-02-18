#include <sqstdio.h>

int sqfgetc (const rStream * stream)
{
    if(stream->readStream != NULL)
    {
        uint8_t c;
        if(stream->readStream(&c) != noError)
            return EOF;
        else
            return (int) c;
    }
    else
        return EOF;
}