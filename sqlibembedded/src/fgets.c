#include <sqstdio.h>

char * sqfgets ( char * restrict s, int size, const rStream * stream )
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
        fputc( s, stream );
        ++s;
        --size;
    }
    *s = '\0';
    return s;
}