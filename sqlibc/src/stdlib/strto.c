#include <sqstdlib.h>
#include <sqstring.h>
#include <sqctype.h>

/*
result cmdlineParseInt(char * token, int * value)
{
    int tokenLength = sqstrlen(token);
    int multiplier = 1;
    int i = tokenLength;
    int parsedValue = 0;
    while(i != 0)
    {
        i--;
        switch(token[i])
        {
            case '0':  break;
            case '1': parsedValue = parsedValue + (1 * multiplier); break;
            case '2': parsedValue = parsedValue + (2 * multiplier); break;
            case '3': parsedValue = parsedValue + (3 * multiplier); break;
            case '4': parsedValue = parsedValue + (4 * multiplier); break;
            case '5': parsedValue = parsedValue + (5 * multiplier); break;
            case '6': parsedValue = parsedValue + (6 * multiplier); break;
            case '7': parsedValue = parsedValue + (7 * multiplier); break;
            case '8': parsedValue = parsedValue + (8 * multiplier); break;
            case '9': parsedValue = parsedValue + (9 * multiplier); break;
            case '-': parsedValue = ~parsedValue; 
                // decrement by one due to twos complement difference
                *value = parsedValue+1;
                return noError;
                break;
            default: return cmdlineInvalidArg;
        }
        multiplier *= 10;
    }
    *value = parsedValue;
    return noError;
}

result strhextoi(char * token, int * value)
{
    int tokenLength = sqstrlen(token);
    unsigned int multiplier = 1;
    int i = tokenLength;
    unsigned parsedValue = 0;
    while(i != 2)
    {
        i--;
        switch(token[i])
        {
            case '0':  break;
            case '1': parsedValue = parsedValue + (0x1 * multiplier); break;
            case '2': parsedValue = parsedValue + (0x2 * multiplier); break;
            case '3': parsedValue = parsedValue + (0x3 * multiplier); break;
            case '4': parsedValue = parsedValue + (0x4 * multiplier); break;
            case '5': parsedValue = parsedValue + (0x5 * multiplier); break;
            case '6': parsedValue = parsedValue + (0x6 * multiplier); break;
            case '7': parsedValue = parsedValue + (0x7 * multiplier); break;
            case '8': parsedValue = parsedValue + (0x8 * multiplier); break;
            case '9': parsedValue = parsedValue + (0x9 * multiplier); break;
            case 'A': case 'a': parsedValue = parsedValue + (0xA * multiplier); break;
            case 'B': case 'b': parsedValue = parsedValue + (0xB * multiplier); break;
            case 'C': case 'c': parsedValue = parsedValue + (0xC * multiplier); break;
            case 'D': case 'd': parsedValue = parsedValue + (0xD * multiplier); break;
            case 'E': case 'e': parsedValue = parsedValue + (0xE * multiplier); break;
            case 'F': case 'f': parsedValue = parsedValue + (0xF * multiplier); break;
            default: return cmdlineInvalidArg;
        }
        multiplier = multiplier << 4;
    }
    *value = (int) parsedValue;
    return noError;
} */

// string to long converter, simpe edition
long int sqstrstol(const char * s)
{
    // skipping leading whitespace
    while(sqisspace(*s)) ++s;
    
    int len = sqstrlen(s);
    // if the token is smaller then 3 then it is not hex
    if(len > 2)
    {
        if((s[0] == '0') && (s[1] == 'x'))
        {
            //return cmdlineParseHex(s, value);
        }
    }
    // not hex, fall through to int parsing
    //return cmdlineParseInt(token, value);
}

long int strtol( const char * s, char ** endptr, int base )
{

}

