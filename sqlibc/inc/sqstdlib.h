#ifndef SQSTDLIB_H
#define SQSTDLIB_H

#include <stddef.h>

unsigned long int strtoul( const char * s, char ** endptr, int base );
long int strtol( const char * s, char ** endptr, int base );
long int strstol(const char * s);

#endif
