#include <sqstdio.h>

int sqputsn( char * s )
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

int sqputs( char * s )
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