#include <sqstdlib.h>
#include <sqstring.h>
#include <sqctype.h>

// string to long converter, simple edition
long int sqstrstol(const char * s)
{
    return sqstrtol(s, 0);
}

long int sqstrtol( const char * s, int base )
{
    long int value = 0;
    char sign = '+';
    // skipping leading whitespace
    while(sqisspace(*s)) ++s;
    // determine sign
    if(*s != '+' && *s != '-')
        sign = '+';
    else
        sign = *(s++);
    // determine base, we only handle hex and decimal
    // leading zeroes just get interpreted as a weird decimal
    if(*s == '0')
    {
        ++s;
        if((base == 0 || base == 16) && (*s == 'x' || *s == 'X'))
        {
            base = 16;
            ++s;
        }
    }
    else
    {
        base = 10;
    }
    int digitcount = 0;
    int multiplier = 1;
    // scan forward (TODO make separate hex and decimal scanner
    while(sqisxdigit(*s))
    {
        digitcount++;
        ++s;
    }
    --s;
    // lets check all characters
    while(digitcount)
    {
        switch(*s)
        {
            case '0':  break;
            case '1': value = value + (0x1 * multiplier); break;
            case '2': value = value + (0x2 * multiplier); break;
            case '3': value = value + (0x3 * multiplier); break;
            case '4': value = value + (0x4 * multiplier); break;
            case '5': value = value + (0x5 * multiplier); break;
            case '6': value = value + (0x6 * multiplier); break;
            case '7': value = value + (0x7 * multiplier); break;
            case '8': value = value + (0x8 * multiplier); break;
            case '9': value = value + (0x9 * multiplier); break;
            case 'A': case 'a': value = value + (0xA * multiplier); break;
            case 'B': case 'b': value = value + (0xB * multiplier); break;
            case 'C': case 'c': value = value + (0xC * multiplier); break;
            case 'D': case 'd': value = value + (0xD * multiplier); break;
            case 'E': case 'e': value = value + (0xE * multiplier); break;
            case 'F': case 'f': value = value + (0xF * multiplier); break;
            // unknown character, just exit
            default: return 0;
        }
        --s;
        multiplier = multiplier * base;
        --digitcount;
    }
    return (sign == '+') ? value : -value;
}

