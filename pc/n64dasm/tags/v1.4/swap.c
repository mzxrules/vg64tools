/*
*   Nintendo 64 Disassembler -- swap.c
*   Copyright (c) 2009  ZZT32 [mbr@64.vg]
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public
*   Licence along with this program; if not, write to the Free
*   Software Foundation, Inc., 51 Franklin Street, Fifth Floor, 
*   Boston, MA  02110-1301, USA
*/

#include <stdio.h>
#include <stdint.h>


/* ----------------------------------------------
   Local variables
   ---------------------------------------------- */

/* Jump table for the swapping functions */
static int (*Swap[0x10000])(int);

/* Init bool */
static int inityet;


/* ----------------------------------------------
   Local functions
   ---------------------------------------------- */

static int
fail ( int w )
{
    return w;
}
   
/* 3210 -> 0123 */
static int
s_le_be ( int w )
{
    return 
    (
        (w & 0xFF000000) >> 24 |
        (w & 0x00FF0000) >> 8  |
        (w & 0x0000FF00) << 8  |
        (w & 0x000000FF) << 24
    );
}

/* 1032 -> 0123 */
static int
s_v64_be ( int w )
{
    return
    (
        ((w & 0xFF000000) >> 8) |
        ((w & 0x00FF0000) << 8) |
        ((w & 0x0000FF00) >> 8) |
        ((w & 0x000000FF) << 8)
    );
}


int
swap_word ( int w, uint16_t m )
{
    if( !inityet )
    {
        int i;
        
        inityet = 1;
        
        for( i = 0; i < 0x10000; i++ )
            Swap[i] = fail;
        
        Swap[0x3210] = s_le_be;
        Swap[0x1032] = s_v64_be;
    }
    
    return Swap[m](w);
}

