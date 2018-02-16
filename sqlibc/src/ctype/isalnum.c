#include <sqctype.h>
#include <sqctypetable.h>

int isalnum( int c )
{
    return(asciiTableCtypes[c].flags & ( ctypeIsDigit | ctypeIsLower | ctypeIsUpper));
}
