#include <sqstdio.h>

int sqfputc(int c, const wStream * stream)
{
    if(stream->writeStream != NULL)
    {
        if(stream->writeStream((uint8_t) c) == noError)
            return c;
        else
            return EOF;
    }
    else
        return EOF;
}