#include "strint.h"

int
strtoint(char * str)
{
    int check, result = 0, len = strlen(str);
    
    /* Empty string */
    if(!len);
    /* Hexadecimal */
    else if(len > 2 && !strncmp(str, "0x", 2) && sscanf(str, "%x", &check) == 1)
        result = check;
    /* Decimal */
    else if(sscanf(str, "%u", &check) == 1)
        result = check;
    return result;
}
