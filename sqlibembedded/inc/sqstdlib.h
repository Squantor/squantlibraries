#ifndef SQSTDLIB_H
#define SQSTDLIB_H

#include <stddef.h>

unsigned long int sqstrtoul(const char * s, char ** endptr, int base);
long int sqstrtol(const char * s, char ** endptr, int base);
long int sqstrstol(const char * s);

#endif
