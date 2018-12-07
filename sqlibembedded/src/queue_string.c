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

#define WRAP(value, len) ((value) & (len))

// helper functions
// search forward for seperator
static uint16_t SeekForwardSep(t_queueString * queue, uint16_t idx)
{
    while(queue->data[idx] != 0)
        idx = WRAP(idx + 1, queue->len);
    return idx;
}

// search forward for not seperator
static uint16_t SeekForwardNotSep(t_queueString * queue, uint16_t idx)
{
    while(queue->data[idx] == 0)
        idx = WRAP(idx + 1, queue->len);
    return idx;
}

// search backward for seperator
static uint16_t SeekBackSep(t_queueString * queue, uint16_t idx)
{
    uint16_t newIndex = idx;
    // first scan backwards for one or more NUL chars while checking the tail
    while(queue->data[newIndex] == 0)
    {
        newIndex = WRAP(newIndex - 1, queue->len);
        // reached end, new index is old index
        if(newIndex == queue->tail)
            return idx;
    }
    // then scan backwards for one or more non NUL characters while checking the tail
    while(queue->data[newIndex] != 0)
    {
        newIndex = WRAP(newIndex - 1, queue->len);
        if(newIndex == queue->tail)
            return idx;
    }
    // return the new index
    return newIndex+1;
}

result queueStringEnqueue(t_queueString *queue, char * s)
{
    if((queue == NULL) || (s == NULL))
        return invalidArg;
        
    uint16_t stringSize = sqstrlen(s);
    if(!(stringSize > 0) || !(stringSize < queue->len))
        return dataInvalid;
    
    // now also add the zero terminator
    stringSize++;
    // do we have enough space to add at the head?
    uint16_t newHead;
    if((stringSize) > (queue->len - queue->head))
    {
        // no, clear the end so we do not find strings later on there
        sqmemset(&(queue->data[queue->head]), 0, queue->len - queue->head);
        // reset head to 0
        newHead = 0;
        // did we overtake the tail?
        if((queue->head + stringSize) > queue->tail)
            // put tail beyond so overtake will detect it
            queue->tail = stringSize;
    }
    else
    {
        // yes, append to head
        newHead = queue->head;
    }
    
    // will the new head overtake the tail?
    if((newHead < queue->tail) && (queue->tail <= (newHead + stringSize)))
    {
        // yes, search new place for head
        uint16_t newtail = newHead + stringSize;
        newtail = SeekForwardSep(queue, newtail);
        queue->tail = SeekForwardNotSep(queue, newtail);
    }
    
    sqstrcpy(&(queue->data[newHead]), s);
    // point to next space
    queue->head = newHead + stringSize;
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
    // no refactor as it would need strlen, strcpy combo
    while(queue->data[newtail] != 0)
    {
        *s = queue->data[newtail];
        newtail++; s++;
    }
    *s = 0;
    newtail = SeekForwardNotSep(queue, newtail);
    queue->tail = newtail;
    return noError;
}

result queueStringPrev(t_queueString * queue, uint16_t * i, char * s)
{
    if((queue == NULL) || (i == NULL) || (s == NULL))
        return invalidArg;
    if((queue->head == queue->tail) || (queue->tail == *i))
        return queueEmpty;
    // search backwards from current index index
    uint16_t indexNew = SeekBackSep(queue, *i);
    if(indexNew == *i)
        return queueEmpty;
    // copy over string to s
    sqstrcpy(s, &(queue->data[indexNew]));
    *i = indexNew;
    return noError;
}

result queueStringNext(t_queueString * queue, uint16_t * i, char * s)
{
    if((queue == NULL) || (i == NULL) || (s == NULL))
        return invalidArg;
    if((queue->head == queue->tail) || (queue->head == *i))
        return queueEmpty;
    uint16_t indexNew = *i;
    indexNew = SeekForwardSep(queue, indexNew);
    // point to begin of string
    indexNew = WRAP(indexNew + 1, queue->len);
    if(queue->head == indexNew)
    {
        return queueEmpty;
    }
    // copy over string to s
    sqstrcpy(s, &(queue->data[indexNew]));
    *i = indexNew;
    return noError;
}