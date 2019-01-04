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

size_t sqstrnlen ( const char * str, size_t num )
{
	size_t len = 0;
    while(str[len] && (len < num))
    {
    	++len;
    }
    // return 0 if this string is not zero terminated
	return len < num ? len : num;
}
