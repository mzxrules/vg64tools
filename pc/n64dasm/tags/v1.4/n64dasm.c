/*
*   Nintendo 64 Disassembler -- n64dasm.c
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
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <stdint.h>
#include "decoder.h"
#include "sym.h"
#include "swap.h"
#include "ansi.h"


/* ----------------------------------------------
   Local variables
   ---------------------------------------------- */

static FILE * in;
static FILE * out;
static int ch;
static int fflag, oflag, Yflag, Gflag, uflag, Uflag, sflag, pflag, aflag, Hflag;
static int Sflag, Eflag, dflag, cflag, Lflag, Oflag;
static unsigned w, pc = 0, S, E;
static char * pager = "less";
static uint16_t order;


/* ----------------------------------------------
   Local functions
   ---------------------------------------------- */

static int
STATUSM ( char * fmt, ... )
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


static void 
show_usage ( char * n )
{
    fprintf
    ( 
       stderr, 
      "usage: %s [-f file] [-o file] [-S offset] [-E offset] [-Y symtab] "
      "[-p address] [-s spacing] [-O order] [-GuUaHdcLh]\n",
      n
    );
    
    exit( EXIT_FAILURE );
}

static void
line_predicate ( unsigned pc, unsigned w, char * dasm )
{
    if( aflag )
    {
        if( cflag )
            fprintf( out, ANSI_SET_FG_WHITE_BOLD "%08X" ANSI_RESET_DEFAULT ": ", pc );
        else
            fprintf( out, "%08X: ", pc );
    }
    
    if( Hflag )
    {
        if( cflag )
            fprintf( out, "("ANSI_SET_FG_CYAN"%08X"ANSI_RESET_DEFAULT") ", w );
        else
            fprintf( out, "(%08X) ", w );
    }
}

static void
print ( unsigned pc, unsigned w, char * dasm )
{
    const char * n;
    
    line_predicate( pc, w, dasm );
    
    if( Yflag )
    {
        if( (n = sym_lookup(pc)) )
        {
            if( !cflag )
                fprintf( out, "%s:\n", n );
            else
                fprintf( out, ANSI_SET_FG_GREEN "%s" ANSI_RESET_DEFAULT ":\n", 
                    n );
            line_predicate( pc, w, dasm );
        }
    }
    
    fprintf( out, "%s%s\n", (Yflag||aflag||Hflag?"        ":""), dasm );
    fflush( out );
}


/* ----------------------------------------------
   Entry point
   ---------------------------------------------- */

int main ( int argc, char ** argv )
{
    static unsigned char buffer[4], dasm[512];
    int fd[2], status;
    in = stdin;
    out = stdout;
    
    STATUSM
    ( 
      ANSI_SET_FG_WHITE_BOLD
      "n64dasm" 
      ANSI_RESET_DEFAULT 
      " version " VERSION "." 
    );
    
    while( (ch = getopt(argc, argv, "f:o:Y:uUs:p:aHS:E:O:dcGL")) != -1 )
    {
        switch( ch )
        {
            case 'f': 
             fflag = 1;
             
             if( !strcmp(optarg, "-") )
                 break;
             
             if( !(in = fopen(optarg, "rb")) )
             {
                 STATUSM( "Unable to access `%s`.", optarg );
                 exit( 1 );
             }
             
             STATUSM( "Reading from `%s`.", optarg );
            break;
            
            case 'o':  
             if( Lflag )
             {
                 STATUSM( "You can't use -L in conjunction with -o." );
                 exit( EXIT_FAILURE );
                 break;
             }
             
             oflag = 1;
             
             if( !strcmp(optarg, "-") )
                 break;
             
             if( !(out = fopen(optarg, "wb")) )
             {
                 STATUSM( "Unable to access `%s`.", optarg );
                 exit( 1 );
             }
             
             STATUSM( "Writing to `%s`.", optarg );
            break;
            
            case 'Y':
             Yflag = 1;
             
             STATUSM( "Reading symbols from `%s`...", optarg );
             STATUSM( "Read %i symbols.", sym_load(optarg) );
            break;
            
            case 's':
             sflag = 1;
             
             mr4kd_spacing( atoi(optarg) );
             
             STATUSM( "Spacing set to %s.", optarg );
            break;
            
            case 'u':
             uflag = 1;
             
             mr4kd_flag_clear( MR4KD_OLOWER );
             
             STATUSM( "Displaying opcodes in upper case." );
            break;
            
            case 'U':
             Uflag = 1;
             
             mr4kd_flag_clear( MR4KD_RLOWER | MR4KD_HLOWER );
             
             STATUSM( "Displaying operands in upper case." );
            break;
            
            case 'p':
             pflag = 1;
                
             if( sscanf( optarg, "%x", &pc ) == 1 )
                STATUSM( "PC set to 0x%08X.", pc );
            break;
            
            case 'a':
             aflag = 1;
             
             STATUSM( "Will display address at left hand side." );
            break;
            
            case 'H':
             Hflag = 1;
             
             STATUSM( "Will display hex representation on left." );
            break;
            
            case 'S':
             Sflag = 1;
             
             sscanf( optarg, "%x", &S );
             
             STATUSM( "Skipping to 0x%08X.", S );
            break;
            
            case 'G':
             Gflag = 1;
             
             STATUSM( "Treating input as a GameShark code.", S );
            break;
            
            case 'E':
             Eflag = 1;
             
             sscanf( optarg, "%x", &E );
             
             STATUSM( "Reading until 0x%08X.", E );
            break;
            
            case 'd':
             dflag = 1;
             
             mr4kd_flag_set( MR4KD_RPREFIX );
             
             STATUSM( "Using dollar sign prefix." );
            break;
            
            case 'c':
             cflag = 1;
             
             mr4kd_flag_set( MR4KD_COLOR );
             
             STATUSM( "Using colors in output." );
            break;
            
            case 'L':
            {
              char * pgr;
              
              if( oflag )
              {
                  STATUSM( "You can't use -o in conjunction with -L." );
                  exit( EXIT_FAILURE );
                  break;
              }
              
              Lflag = 1;
              
              pgr = getenv( "PAGER" );
              
              if( pgr )
                pager = pgr;
              
              STATUSM( "Using `%s` to page output.", pager );
            }
            break;
            
            case 'O':
             Oflag = 1;
             unsigned tmpw;
             
             if( !sscanf( optarg, "%X", &tmpw ) )
             {
                goto invalid_flag;
             }
             
             order = (uint16_t)tmpw;
             
             if( order != 0x3210 && order != 0x1032 && order != 0x0123 )
                 goto invalid_flag;
             
             STATUSM( "Swapping %04X -> %s.", order, "0123" );
             
             break;
             
         invalid_flag:
             STATUSM( "Invalid flag to -O: %s.", optarg );
             Oflag = 0;
            break;
            
            case '?':
            default:
             show_usage( argv[0] );
            break;
        }
    }
    
    /* Start the pager */
    if( Lflag )
    {
        int v;
        
        pipe( fd );
        
        if( !fork() )
        {
            /* Set up pipes */
            close( fd[1] );
            close( 0 );
            dup( fd[0] );
            
            /* Run the pager */
            v = execlp( pager, pager, "-SR#", "8", NULL );
            
            exit( -1 );
        }
        
        close( 1 );
        dup( fd[1] );
        close( fd[0] );
    }
        
    
    if( Sflag )
        fseek( in, S, SEEK_SET );
    
    if( Gflag )
        goto gs;
    
    while( !feof(in) )
    {
        if( Eflag && ftell(in) >= E )
            break;
        
        fread( buffer, 1, 4, in );
        w = buffer[0] << 24 | buffer[1] << 16 | buffer[2] << 8 | buffer[3];
        
        /* Swap the buffer? */
        if( Oflag )
        {
            w = swap_word( w, order );
        }
        
        mr4kd_disassemble( w, pc, (char*)dasm );
        
        print( pc, w, (char*)dasm );
        
        pc += 4;
    }

ret:
    
    if( Lflag )
    {
        fflush( out );
        fclose( out );
        close( fd[1] );
        
        wait( &status );
    }
    
    return 0;
    
gs:
    
    while( !feof(in) )
    {
        unsigned a, v;
        
        if( fscanf( in, "%08X %04X", &a, &v ) != 2 )
            break;
        a &= 0xF0FFFFFF;
        pc = a;
        w = (v << 16);
        if( fscanf( in, "%08X %04X", &a, &v ) != 2 )
            break;
        a &= 0xF0FFFFFF;
        w |= v;
        if( a - pc != 2 )
            STATUSM( "PC jumped from %08X to %08X!", pc, a );
        
        mr4kd_disassemble( w, pc, (char*)dasm );
        
        print( pc, w, (char*)dasm );
    }
    
    goto ret;
}
