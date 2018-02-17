#include <sqstdio.h>

int sqfputc(int c, const sqFILE * stream)
{
    if(stream->streamWrite != NULL)
    {
        return stream->streamWrite((uint8_t) c);
    }
    else
        return EOF;
}