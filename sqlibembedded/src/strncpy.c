#include <sqstring.h>

char * sqstrncpy(char * restrict s1, const char * restrict s2, size_t n)
{
    char * rc = s1;
    while(( n > 0) && (*s1++ = *s2++))
    {
        --n;
    }
    while(n-- > 1)
    {
        *s1++ = '\0';
    }
    return rc;
}

char * sqstrcpy(char * restrict s1, const char * restrict s2)
{
    char * r = s1;
    while((*s1++ = *s2++))
        ;
    return r;
}
