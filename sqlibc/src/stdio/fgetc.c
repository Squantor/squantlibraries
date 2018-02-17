#include <sqstdio.h>

int sqfgetc (const sqFILE * stream)
{
    if(stream->streamRead != NULL)
    {
        uint8_t c;
        stream->streamRead(&c);
        return (int)c;
    }
    else
        return EOF;
}