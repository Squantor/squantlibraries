#ifndef SQSTDIODEFS_H
#define SQSTDIODEFS_H

#include <stdint.h>

struct sqInternalFILE
{
    // function pointer to write to stream
    int (*streamWrite)(uint8_t);
    // function pointer to read from stream
    int (*streamRead)(uint8_t *);
};

#endif