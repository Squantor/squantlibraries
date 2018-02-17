#include <sqctype.h>
#include <sqctypetable.h>

int sqisspace( int c )
{
    return (asciiTableCtypes[c].flags & (ctypeIsSpace));
}
