#ifndef SQSTRING_H
#define SQSTRING_H

#include <stddef.h>

size_t sqstrlen ( const char * str );
size_t sqstrnlen ( const char * str, size_t num );

void * sqmemchr( const void * s, int c, size_t n );
void * sqmemset( void * s, int c, size_t n );
void * sqmemmove( void * s1, const void * s2, size_t n );
void * sqmemcpy( void * restrict s1, const void * restrict s2, size_t n );
int sqmemcmp( const void * s1, const void * s2, size_t n );

#endif
