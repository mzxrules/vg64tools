#include "strint.h"

int isdec(char * str)
{
    int result;
    sscanf(str, "%u", &result);
    return (result != -1) ? true : false;
}

int ishex(char * str)
{
    int result;
    sscanf(str, "%x", &result);
    return (result != -1) ? true : false;
}

int
strtoint(char * str)
{
    int result = 0, len = strlen(str);
    
    /* Empty string */
    if(!len);
    /* Hexadecimal */
    else if(len > 2 && !strncmp(str, "0x", 2) && ishex(str))
        sscanf(str, "%x", &result);
    /* Decimal */
    else if(isdec(str))
        sscanf(str, "%i", &result);
    return result;
}
