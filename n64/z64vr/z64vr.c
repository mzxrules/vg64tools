/*
 Feel free to do as you like with this, so long as I (spinout) am credited as the original author.
*/

#define TEXT_OFF 0x80221EAA

void _start(void)	/* What makes this hack work is that it runs (almost) right after the text is DMA'd from ROM*/
{
    char (*text)[0xC0] = (void*)TEXT_OFF;	/* Text fresh from ROM */
    int i = 0;	/* Counter */
    while (1)	/* mips-gcc messes up for loops */
    {
        if ( (*text)[i-1] > 0x1F )	/* Don't edit a special text command! */
        {
            if ( ((*text)[i] == 97) || ((*text)[i] == 101) || ((*text)[i] == 105) || ((*text)[i] == 117) ) /* Lowercase */
            {
                (*text)[i] = 111;
            }
            else if ( ((*text)[i] == 65) || ((*text)[i] == 69) || ((*text)[i] == 73) || ((*text)[i] == 85) ) /* Uppercase */
            {
                (*text)[i] = 79;
            }
        }
        else if ( ( (*text)[i] == 2 ) || ( i == 0xC0 ) )	/* \x02 = EOF, 0xC0 = max len*/
        {
            break;
        }
        i++;
    }
}
