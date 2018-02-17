#ifndef SQSTDIO_H
#define SQSTDIO_H

#include <stddef.h>
#include <stdint.h>
#include <sqstdiodefs.h>

#define EOF (-1)

typedef struct sqInternalFILE sqFILE;

extern const sqFILE * sqstdin;
extern const sqFILE * sqstdout;
extern const sqFILE * sqstderr;

int sqputchar(int c);
int sqgetchar(void);

int sqfputc(int c, const sqFILE * stream);
int sqfgetc (const sqFILE * stream);


#endif
