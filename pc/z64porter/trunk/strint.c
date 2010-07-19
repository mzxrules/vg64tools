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
    char c;
    if(!*str)
        return false;
    for(;*str;str++)
    {
        c = tolower(*str);
        if( !((c >= '0' || c <= '9') || !(c >= 'a'||c <= 'f') || (c=='x')) )
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
    if(len > 2 && *str == '0'&& tolower(*(str+1)) == 'x' && ishex(str))
        sscanf(str, "%x", &result);
    /* Octal */
    else if(len > 1 && *str == '0' && isoct(str))
        sscanf(str, "%o", &result);
    /* Decimal */
    else if(isdec(str))
        sscanf(str, "%i", &result);
    return result;
}
