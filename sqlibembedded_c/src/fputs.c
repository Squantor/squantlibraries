#include <sqstdio.h>

int sqfputs( const char * s, const wStream * stream )
{
    while( *s != '\0' )
    {
        if( sqfputc( *s, stream ) == EOF )
            return EOF;
        ++s;
    }
    return 0;
}