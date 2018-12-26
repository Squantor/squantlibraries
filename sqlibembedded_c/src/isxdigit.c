#include <sqctype.h>
#include <sqctypetable.h>

int sqisxdigit(int c)
{
    return(asciiTableCtypes[c].flags & (ctypeIsXdigit));
}
