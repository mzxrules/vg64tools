/*
*   Zelda 64 Actor Inspector -- func.c
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
#include <string.h>
#include <stdarg.h>
#include <stdint.h>
#include <glib.h>
#include "ansi.h"


/* Specification for formatting... */
static struct FSpec
{
    int maxval;
    int divby;
    int decplaces;
    char * suffix;
}
spec[] = 
{
    { 1024,         1.0,           0, "b" },
    { 1024 * 1024,  1024.0,        2, "k" },
    { -1,           1024 * 1024.0, 2, "m" },
    { 0,                                  }
};
    

/* Format an integer value into something human-readable */
int
format_value ( char * tgt, unsigned val )
{
    double nval;
	struct FSpec * f;
    int v;
    
    f = &spec[0];
    
    while( f->suffix )
    {
        /* Is this the last one? */
        if( !(f+1)->suffix )
        {
            /* yeah, we have to use it */
            break;
        }
        
        /* Do we fit into this category? */
        if( f->maxval > val )
        {
            /* Yep, use it */
            break;
        }
        
        /* Go to next */
        f++;
    }
    
    /* Calculate the value to print */
    nval = (double)val / f->divby;
    
    /* Format */
    v = sprintf( tgt, "%.*f%s", f->decplaces, nval, f->suffix );
    
    return v;
}


int
MESG ( char * fmt, ... )
{
    va_list ap;
    char format[512];
    int len;
    
    sprintf( format, "[" ANSI_SET_FG_BLUE "-" ANSI_RESET_DEFAULT "] %s\n", fmt );
    
    va_start( ap, fmt );
    len = vfprintf( stderr, format, ap );
    va_end( ap );
    
    return len;
}


int
ERROR ( char * fmt, ... )
{
    va_list ap;
    char format[512];
    int len;
    
    sprintf( format, "[" ANSI_SET_FG_RED "!" ANSI_RESET_DEFAULT "] %s\n", fmt );
    
    va_start( ap, fmt );
    len = vfprintf( stderr, format, ap );
    va_end( ap );
    
    return len;
}


uint32_t
get_val32 ( uint8_t * data )
{
    uint32_t local;
    
    local = *(uint32_t*)data;
    
    return g_ntohl( local );
}

