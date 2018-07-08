#ifndef QUEUE_STRING_H
#define QUEUE_STRING_H

#include <results.h>
#include <stdint.h>

typedef struct queueString
{
    // mask be power of two!
    const uint16_t    mask;
    uint16_t    head;
    uint16_t    tail;
    char *      data;
} t_queueString;

// add string, if it does not fit, oldest gets deleted
result queueStringEnqueue(t_queueString * queue, char * s);
result queueStringDequeue(t_queueString *queue, char * s);



#endif
