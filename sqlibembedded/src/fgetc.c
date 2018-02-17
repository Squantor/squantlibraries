#include <sqstdio.h>

int sqfgetc (const sqFILE * stream)
{
    if(stream->streamRead != NULL)
    {
        uint8_t c;
        if(stream->streamRead(&c) == EOF)
            return EOF;
        else
            return (int) c;
    }
    else
        return EOF;
}