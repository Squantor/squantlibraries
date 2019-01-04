#include <sqstdio.h>

int sqputchar(int c)
{
    return sqfputc(c, sqstdout);
}