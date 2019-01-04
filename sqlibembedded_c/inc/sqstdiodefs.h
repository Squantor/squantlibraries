#ifndef SQSTDIODEFS_H
#define SQSTDIODEFS_H

#include <stdint.h>
#include <results.h>

typedef struct 
{
    result (*readStream)(char *);
} rStream;

typedef struct 
{
    result (*writeStream)(char);
} wStream;

#endif