#include <sqctype.h>
#include <sqctypetable.h>

int isxdigit(int c)
{
    return(asciiTableCtypes[c].flags & (ctypeIsXdigit));
}
