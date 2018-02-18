#ifndef SQSTDIODEFS_H
#define SQSTDIODEFS_H

#include <stdint.h>
#include <results.h>

typedef struct 
{
    result (*readStream)(uint8_t *);
} rStream;

typedef struct 
{
    result (*writeStream)(uint8_t);
} wStream;

#endif