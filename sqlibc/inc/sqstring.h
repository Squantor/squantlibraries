#ifndef SQSTRING_H
#define SQSTRING_H

#include <stddef.h>

size_t strlen ( const char * str );
size_t strnlen ( const char * str, size_t num );
int strcmp(const char * s1, const char * s2);
char * strncpy( char * restrict s1, const char * restrict s2, size_t n );

void * memchr( const void * s, int c, size_t n );
void * memset( void * s, int c, size_t n );
void * memmove( void * s1, const void * s2, size_t n );
void * memcpy( void * restrict s1, const void * restrict s2, size_t n );
int memcmp( const void * s1, const void * s2, size_t n );
char * strtok( char * restrict s1, const char * restrict s2 );
char * strtokns(char * restrict s1, const char * restrict s2, char ** pos);

#endif
