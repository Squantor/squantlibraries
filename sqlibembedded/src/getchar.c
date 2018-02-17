#include <sqstdio.h>

int sqgetchar(void)
{
    return sqfgetc(sqstdin);
}