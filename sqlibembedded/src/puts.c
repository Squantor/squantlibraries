#include <sqstdio.h>

int sqputsn( const char * s )
{
    while( *s != '\0' )
    {
        if( sqfputc( *s, sqstdout ) == EOF)
        {
            return EOF;
        }
        ++s;
    }
    return 0;
}

int sqputs( const char * s )
{
    while( *s != '\0' )
    {
        if( sqfputc( *s, sqstdout ) == EOF)
        {
            return EOF;
        }
        ++s;
    }
    sqfputc( '\n', sqstdout );
    return 0;
}
