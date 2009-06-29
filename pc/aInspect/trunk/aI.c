/*
*   Zelda 64 Actor Inspector -- aI.c
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
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <glib.h>
#include <errno.h>
#include "aI.h"


/* ----------------------------------------------
   Global variables
   ---------------------------------------------- */

/* Section names */
const char * 
za_section_names[] =
{
   ".text", 
   ".data",
   ".rodata",
   ".bss"
};

/* Relocation types */
const char *
za_reloc_types[] = 
{
    NULL,          NULL,        "pointer",    NULL,
    "jump target", "lui/ori#1", "lui/ori#2",  NULL
};


/* ----------------------------------------------
   Global functions
   ---------------------------------------------- */

/* Open an actor file */
ZAct *
za_open ( char * filename )
{
    FILE * h;
    ZAct * ret;
    uint32_t h_offset;
    uint8_t buff[4];
    int i;
    
    /* Try to open */
    if( !(h = fopen(filename, "rb")) )
    {
        /* Failure */
        ERROR( "Couldn't open file: %s\n", strerror(errno) );
        return NULL;
    }
    
    /* Allocate memory for return */
    ret = calloc( sizeof(ZAct), 1 );
    ret->fname = strdup( filename );
    
    /* Get filesize */
    ret->fhandle = h;
    fseek( h, 0, SEEK_END );
    ret->fsize = ftell( h );
    
    /* Read -offset to actor header data */
    fseek( h, -4, SEEK_END );
    fread( buff, sizeof(buff), 1, h );
    
    /* Get a 32-bit value from it */
    h_offset = get_val32( buff );
    ret->h_offset = h_offset;
    
    /* Check it... */
    if( h_offset > ret->fsize - 4 || (h_offset & 3) )
    {
        int c;
        
        c = (signed)h_offset;
        
        /* Not a valid offset */
        ERROR( 
            "`%s`: $%s0x%x is not a valid offset to actor section header.",
            filename,
            (c < 0) ? "-" : "",
            h_offset
        );
        exit( EXIT_FAILURE );
    }
    
    /* Read the header! */
    fseek( h, -ret->h_offset, SEEK_END );
    fread( &ret->header, sizeof(struct sect_header_t), 1, h );
    
    /* Swap it... */
    for( i = 0; i < sizeof(struct sect_header_t)/4; i++ )
        ((uint32_t*)&ret->header)[i] = g_ntohl( ((uint32_t*)&ret->header)[i] );
    
    /* We're done */
    return ret;
}

/* Get a relocation */
void
za_get_reloc ( ZAct * h, int r_id, uint32_t * tgt )
{
    uint8_t buff[4];
    
    /* Seek to address */
    fseek( 
        h->fhandle, 
        -h->h_offset + sizeof(struct sect_header_t) + r_id * 4,
        SEEK_END
    );
    
    /* Read word */
    fread( buff, sizeof(buff), 1, h->fhandle );
    
    /* Convert value */
    *tgt = get_val32( buff );
}


/* ----------------------------------------------
   Local variables - command line arguments
   ---------------------------------------------- */
   
/* Getopt format string */
static char * arg_fmt = "lrmhS:T:W:";

/* Action flags */
static int lflag;       /* List sections and their sizes  */
static int rflag;       /* List relocations               */
static int mflag;       /* Relocate actor                 */

/* Generic flags */
static int hflag;       /* Format integral values (k,m)   */
static int Sflag;       /* Original address base of actor */
static uint32_t Sval;

/* Relocate options */
static int Tflag;       /* Target address of actor        
static uint32_t Tval;*/
static int Wflag;       /* Filename to write to           
static char * Wval;*/

/* Input file */
static char * input_filename;


/* ----------------------------------------------
   Local functions
   ---------------------------------------------- */
   
/* Check if other action flags have been set */
static int
have_action ( void )
{
    return lflag || rflag || mflag;
}

/* Check if action already set, and quit */
static void
check_action ( void )
{
    if( !have_action() )
        return;
    
    ERROR( "Can't specify more than one action." );
    exit( EXIT_FAILURE );
}

/* Process arguments */
static void
do_args ( int argc, char ** argv )
{
    int c, index;
    
    /* Loop through arguments */
    while( (c = getopt(argc, argv, arg_fmt)) != -1 )
    {
        switch( c )
        {
            /*
             *  Actions
             */
            
            case 'l':
            {
              /* Check for dupes */
              check_action();
              
              MESG( "Listing sections." );
              
              lflag = 1;
            }
            break;
            
            case 'r':
            {
              /* Check for dupes */
              check_action();
              
              MESG( "Listing relocations." );
              
              rflag = 1;
            }
            break;
            
            case 'm':
            {
              /* Check for dupes */
              check_action();
              
              /*MESG( "Relocating actor" );*/
              ERROR( "Not yet implemented. " );
              exit( EXIT_FAILURE );
              
              mflag = 1;
            }
            break;
            
            
            /*
             *  Generic flags
             */
            
            case 'S':
            {
              /* Read value */
              sscanf( optarg, "%X", &Sval );
              
              MESG( "Setting base address to 0x%08X.", Sval );
              
              Sflag = 1;
            }
            break;
            
            case 'h':
            {
              MESG( "Formating integral values." );
              
              hflag = 1;
            }
            break;
            
            
            
            default:
             exit( EXIT_FAILURE );
        }
    }
    
    /* Get 1 filename */
    for( index = optind; index < argc; index++ )
    {
        /* Set input file */
        input_filename = argv[index];
    }
    
    /* Did we set a filename...? */
    if( input_filename )
    {
        /* Display */
        MESG( "Reading from \"%s\".", input_filename );
    }
    else
    {
        /* None provided, whoops */
        ERROR( "Please provide the filename of an actor." );
        exit( EXIT_FAILURE );
    }
}

/* List the sections of this actor */
static void
list_sections ( ZAct * h )
{
    int i, offset;
    char size_str[64];
    
    offset = 0;
    
    /* header */
    printf( "%-10sADDRESS\tSIZE\n", "NAME" );
    
    for( i = 0; i < ZA_SECT_COUNT; i++ )
    {
        /* Format size string */
        if( hflag )
        {
            /* Human readable format */
            format_value( size_str, h->header.size[i] );
        }
        else
        {
            /* Plain ol' bytes */
            sprintf( size_str, "%i", h->header.size[i] );
        }
        
        /* Display it */
        printf( 
            "%-10s0x%08X\t%s\n",
            za_section_names[i],
            Sval + offset,
            size_str
        );
        
        /* Update offset */
        offset += h->header.size[i];
    }
}

/* List the relocations in this actor */
static void
list_relocations ( ZAct * h )
{
    int i;
    uint32_t r;
    
    int base = 0;
    int last_sect = -1;
    
    printf( "%-10s%-20s%-10s\t%-8s\n",
        "SECTION",
        "TYPE",
        "REL ADDR",
        "ADDR"
    );
    
    for( i = 0; i < h->header.reloc; i++ )
    {
        int str_sec;
        
        za_get_reloc( h, i, &r );
        
        str_sec = ((r >> 28 & 0xF) - 4) / 4;
        
        if( last_sect == -1 || last_sect != str_sec )
        {
            last_sect = str_sec;
            
            if( str_sec )
                base += h->header.size[str_sec-1];
        }
        
        if( str_sec < 0 )
            continue;
        
        printf( 
            "%-10s%-20s0x%08X\t0x%08X\n", 
            za_section_names[str_sec],
            za_reloc_types[r >> 24 & 0xF],
            (r & 0x00FFFFFF),
            Sval + base + (r & 0x00FFFFFF)
        );
    }
}



int
main ( int argc, char ** argv )
{
    ZAct * h;
    
    /* Header */
	MESG( 
        "%s", 
        PROGRAM_NAME " " 
        PROGRAM_VERSION 
        " (" __DATE__ " " __TIME__ ")" 
    );
    
    /* Process our arguments */
    do_args( argc, argv );
    
    /* Check status */
    if( !have_action() )
    {
        ERROR( "You didn't specify an action with one of the -lrm options." );
        exit( EXIT_FAILURE );
    }
    
    /* Check arguments... */
    if( mflag )
    {
        /* We need the following flags */
        if( !Sflag || !Tflag || !Wflag )
        {
            ERROR( "You need to specify values with the -STW flags in conjunc"
            "tion with the -m flag." );
            exit( EXIT_FAILURE );
        }
    }
    
    /* Open our actor file */
    h = za_open( input_filename );
    
    /* Error... */
    if( !h )
    {
        exit( EXIT_FAILURE );
    }
    
    
    /* List sections */
    if( lflag )
    {
        list_sections( h );
        goto end;
    }
    
    /* List relocations */
    if( rflag )
    {
        list_relocations( h );
        goto end;
    }
  
  end:
        
    return 0;
}

