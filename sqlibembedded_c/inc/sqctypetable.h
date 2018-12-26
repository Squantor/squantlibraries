#ifndef SQCTYPETABLE_H
#define SQCTYPETABLE_H

#include <stdint.h>

typedef enum 
{
    ctypeIsNone = 0x0000,
    ctypeIsBlank = 0x0001,
    ctypeIsCntrl = 0x0002,
    ctypeIsDigit = 0x0004,
    ctypeIsGraph = 0x0008,
    ctypeIsLower = 0x0010,
    ctypeIsPrint = 0x0020,
    ctypeIsPunct = 0x0040,
    ctypeIsSpace = 0x0080,
    ctypeIsUpper = 0x0100,
    ctypeIsXdigit = 0x0200,
    
} ctypeflags;

typedef struct 
{
    uint16_t flags;  
} ctypeEntry;

extern const ctypeEntry asciiTableCtypes[128];

#endif