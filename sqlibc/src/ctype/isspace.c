#include <sqctype.h>
#include <sqctypetable.h>

int isspace( int c )
{
    return (asciiTableCtypes[c].flags & (ctypeIsSpace));
}
