/*
The MIT License (MIT)

Copyright (c) 2018 Anton Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <results.h>
#include <queue_string.h>
#include <sqstring.h>

#define WRAP(value, mask) ((value) & (mask))

result queueStringEnqueue(t_queueString *queue, char * s)
{
    if((queue == NULL) || (s == NULL))
        return invalidArg;
        
    uint16_t stringSize = sqstrlen(s);
    if(!(stringSize > 0) || !(stringSize < queue->mask))
        return dataInvalid;
    
    // now also add the zero terminator
    stringSize++;
    // do we have enough space to add at the head?
    uint16_t indexAdd;
    if((stringSize) > (queue->mask - queue->head))
    {
        // no, clear the end so we do not find strings later on there
        sqmemset(&(queue->data[queue->head]), 0, queue->mask - queue->head);
        indexAdd = 0;
        // are we going overtake the tail?
        if((queue->head < queue->tail) || (queue->tail <= stringSize))
        {
            // yes, shift tail to future head and search from there
            uint16_t newtail = stringSize;
            while(queue->data[newtail] != 0)
            {
                newtail = WRAP(newtail + 1, queue->mask);
            }
            // skip over the found zero terminators
            while(queue->data[newtail] == 0)
            {
                newtail = WRAP(newtail + 1, queue->mask);
            }            
            queue->tail = newtail;            
        }
    }
    else
    {
        indexAdd = queue->head;
        // are we going overtake the tail?
        if((queue->head < queue->tail) && (queue->tail <= (queue->head + stringSize)))
        {
            // yes, shift tail to future head and search from there
            uint16_t newtail = queue->head + stringSize;
            while(queue->data[newtail] != 0)
            {
                newtail = WRAP(newtail + 1, queue->mask);
            }
            // skip over the found zero terminator
            queue->tail = WRAP(newtail + 1, queue->mask);
        }
    }
    
    // TODO, refactor into strcpy
    while(*s != 0)
    {
        queue->data[indexAdd] = *s;
        s++; indexAdd++;
    }
    // zero terminate
    queue->data[indexAdd] = 0;
    // point to next spare location
    queue->head = indexAdd+1;
    return noError;
}

result queueStringDequeue(t_queueString *queue, char * s)
{
    if((queue == NULL) || (s == NULL))
        return invalidArg;
    if(queue->head == queue->tail)
        return queueEmpty;
    
    uint16_t newtail = queue->tail;
    // dequeue into s until size or zero
    while(queue->data[newtail] != 0)
    {
        *s = queue->data[newtail];
        newtail++; s++;
    }
    *s = 0;
    // then scan terminators until we find something or head is reached
    while(queue->data[newtail] == 0)
        newtail++;
    queue->tail = newtail;
    return noError;
}