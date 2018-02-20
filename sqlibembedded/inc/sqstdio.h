#ifndef SQSTDIO_H
#define SQSTDIO_H

#include <stddef.h>
#include <stdint.h>
#include <sqstdiodefs.h>

#define EOF (-1)

typedef struct sqInternalFILE sqFILE;

extern const rStream * sqstdin;
extern const wStream * sqstdout;

int sqputchar( int c );
int sqgetchar( void );
int sqputs( const char * s );
int sqputsn( const char * s );

int sqfputc( int c, const wStream * stream );
int sqfgetc( const rStream * stream );
int sqfputs( const char * s, const wStream * stream );
char * sqfgets ( char * restrict s, int size, const rStream * stream );


#endif
