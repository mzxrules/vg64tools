/*
*   Nintendo 64 Disassembler -- sym.c
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
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "sym.h"


/* ----------------------------------------------
   Local variables
   ---------------------------------------------- */

static GHashTable * symbols;
static int symcount = -1;


/* ----------------------------------------------
   Global variables
   ---------------------------------------------- */

int longest_name;


/* ----------------------------------------------
   Local functions
   ---------------------------------------------- */

static void
sym_init ( void )
{
    symcount = 0;
    symbols = g_hash_table_new( g_direct_hash, g_direct_equal );
}


/* ----------------------------------------------
   Global functions
   ---------------------------------------------- */

int
sym_load ( char * file )
{
    FILE * h;
    unsigned a;
    char buff[512];
    
    if( !(h = fopen(file, "r")) )
        return -1;
    
    if( symcount == -1 )
        sym_init();
    
    while( !feof(h) )
    {
        fscanf( h, "%x,%s", &a, buff );
        
        g_hash_table_insert( symbols, (void*)a, strdup(buff) );
        
        if( strlen(buff) > longest_name )
            longest_name = strlen( buff );
        
        symcount++;
    }
    
    return symcount;
}

const char *
sym_lookup ( unsigned a )
{
    return g_hash_table_lookup( symbols, (void*)a );
}

