#ifndef QUEUE_STRING_H
#define QUEUE_STRING_H

#include <results.h>
#include <stdint.h>

typedef struct
{
    uint16_t    mask;
    uint16_t    head;
    uint16_t    tail;
    char *      data[];
} t_queueString;



#endif
