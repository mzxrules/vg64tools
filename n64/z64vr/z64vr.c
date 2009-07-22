#define TEXT_OFF 0x80221EAA

void _start(void)
{
    char (*text)[0xC0] = (void*)TEXT_OFF;
    int i = 0;
    while (1)
    {
        if ( (*text)[i-1] > 0x1F )
        {
            if ( ((*text)[i] == 97) || ((*text)[i] == 101) || ((*text)[i] == 105) || ((*text)[i] == 117) )
            {
                (*text)[i] = 111;
            }
            else if ( ((*text)[i] == 65) || ((*text)[i] == 69) || ((*text)[i] == 73) || ((*text)[i] == 85) )
            {
                (*text)[i] = 79;
            }
        }
        else if ( ( (*text)[i] == 2 ) || ( i == 0xC0 ) )
        {
            break;
        }
        i++;
    }
}
