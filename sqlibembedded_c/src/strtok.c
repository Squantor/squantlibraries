#include <sqstring.h>

// strtok variant with no static variable
char * sqstrtok_r(char * restrict s1, const char * restrict s2, char ** pos)
{
    char * tmp = *pos;
    const char * p = s2;

    if(s1 != NULL)
    {
        /* new string */
        tmp = s1;
    }
    else
    {
        /* old string continued */
        if(tmp == NULL)
        {
            /* No old string, no new string, nothing to do */
            *pos = tmp;
            return NULL;
        }
        s1 = tmp;
    }

    /* skipping leading s2 characters */
    while(*p && *s1)
    {
        if(*s1 == *p)
        {
            /* found seperator; skip and start over */
            ++s1;
            p = s2;
            continue;
        }
        ++p;
    }

    if(!*s1)
    {
        /* no more to parse */
        return(*pos = tmp = NULL);
    }

    /* skipping non-s2 characters */
    tmp = s1;
    while(*tmp)
    {
        p = s2;
        while(*p)
        {
            if(*tmp == *p++)
            {
                /* found seperator; overwrite with '\0', position tmp, return */
                *tmp++ = '\0';
                (*pos) = tmp;
                return s1;
            }
        }
        ++tmp;
    }

    /* parsed to end of string */
    tmp = NULL;
    *pos = tmp;
    return s1;
}
