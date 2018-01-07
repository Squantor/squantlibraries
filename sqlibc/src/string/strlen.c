#include <sqstring.h>

size_t sqstrlen ( const char * str )
{
	size_t len = 0;
    while(str[len])
    {
    	++len;
    }
	return len;
}
