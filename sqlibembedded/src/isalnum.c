#include <sqctype.h>
#include <sqctypetable.h>

int sqisalnum( int c )
{
    return(asciiTableCtypes[c].flags & ( ctypeIsDigit | ctypeIsLower | ctypeIsUpper));
}
