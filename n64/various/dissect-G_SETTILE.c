#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct val_t
{
    char * name;
    int shamt;
    int size;
};

struct val_t
values[] =
{
    { "Opcode",  56, 8 },
    { "Format",  53, 3 },
    { "Size",    51, 2 },
    { "Line",    41, 9 },
    { "Tmem",    32, 9 },
    { "Tile",    24, 3 },
    { "Palette", 20, 4 },
    { "Cmt",     18, 2 },
    { "Maskt",   14, 4 },
    { "Shiftt",  10, 4 },
    { "Cms",     8,  2 },
    { "Masks",   4,  4 },
    { "Shifts",  0,  4 },
    { NULL }
};

uint32_t w0, w1;

int
main ( int argc, char ** argv )
{
    int i;
    
    /* Read values from standard input */
    while( fscanf(stdin, "%08X %08X", &w0, &w1) == 2 )
    {
        /* Display instruction as prerequisite */
        printf( "Instruction: 0x%08X%08X\n", w0, w1 );
        
        /* Loop through values to display */
        for( i = 0; values[i].name; i++ )
        {
            int s, mask;
            uint32_t * w, val;
            
            /* Set which word to read */
            if( values[i].shamt > 32 )
            {
                w = &w0;
                s = values[i].shamt - 32;
            }
            else
            {
                w = &w1;
                s = values[i].shamt;
            }
            
            /* Build mask */
            mask = (1 << values[i].size) - 1;
            
            /* Pull value */
            val = (*w >> s) & mask;
            
            /* Display it */
            printf( "%-7s: %8X\n", values[i].name, val );
        }
        
        /* Newline */
        printf( "\n" );
    }
    
    return EXIT_SUCCESS;
}

