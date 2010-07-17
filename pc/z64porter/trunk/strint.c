#include "strint.h"

int isdec(char * str)
{
    if(!*str)
        return false;
    for(;*str;str++)
    {
        if(*str < '0' || *str > '9')
            return false;
    }
    return true;
}

int isoct(char * str)
{
    if(!*str)
        return false;
    for(;*str;str++)
    {
        if(*str < '0' || *str > '7')
            return false;
    }
    return true;
}

int ishex(char * str)
{
    if(!*str)
        return false;
    for(;*str;str++)
    {
        if( !(*str >= '0' && *str <= '9') || !(toupper(*str) >= 'A' && toupper(*str) <= 'F') || (toupper(*str) != 'X') )
            return false;
    }
    return true;
}

int
strtoint(char * str)
{
    int result = 0, len = strlen(str);
    
    /* Empty string */
    if(!len);
    /* Hexadecimal */
    if(len > 2 && ( *(str+1) == 'x' || *(str+1) == 'X') && ishex(str))
        sscanf("%x", str, &result);
    /* Octal */
    else if(isoct(str))
        sscanf("%o", str, &result);
    /* Decimal */
    else if(isdec(str))
        sscanf("%i", str, &result);
    
    return result;
}
