#ifndef SQSTDIO_H
#define SQSTDIO_H

#include <stddef.h>
#include <stdint.h>
#include <sqstdiodefs.h>

#define EOF (-1)

typedef struct sqInternalFILE sqFILE;

extern const rStream * sqstdin;
extern const wStream * sqstdout;

int sqputchar(int c);
int sqgetchar(void);

int sqfputc(int c, const wStream * stream);
int sqfgetc (const rStream * stream);


#endif
