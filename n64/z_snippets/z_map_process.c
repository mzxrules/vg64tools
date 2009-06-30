/*
*   Rewritten `z_map_process` function
*   Addresses: 0x8009840C(DBG), 0x800817A0(US 1.0)
*   Copyright (c) 2009  Marshall B. Rogers [mbr@64.vg]
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
   Data types
   ---------------------------------------------- */

typedef uint8_t u8;

typedef void (*MapByteHandler)
(
    void *,
    void *
);


/* ----------------------------------------------
   Variable declarations
   ---------------------------------------------- */

/* @0x801274A0 in debug ROM; @0x800F8F70 in OoT 1.0 */
extern MapByteHandler type_handlers[];



/* ----------------------------------------------
   Global functions
   ---------------------------------------------- */

int
z_map_process ( void * c, void * map )
{
    u8 * data, b;
    
    data = map;
    
    /* Byte read loop */
    while( (b = *data) != 0x14 )
    {
        /* Within limits? */
        if( b < 0x1A )
        {
            /* Call associated handler */
            type_handlers[b]( c, data );
        }
        
        /* Update pointer */
        data += 8;
    }
    
    return 0;
}

