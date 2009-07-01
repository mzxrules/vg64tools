#include <stdio.h>
#include <glib.h>
#include <stdint.h>
#include <ctype.h>
#include "../memory/memory.h"
#include "../r4300/r4300.h"

#define MMASK       (0x007FFFFFUL)
#define MSWAP(x)                \
(                               \
    (x) >> 24 & 0x000000FF |    \
    (x) >> 16 & 0x0000FF00 |    \
    (x) << 16 & 0x00FF0000 |    \
    (x) << 24 & 0xFF000000      \
);

#define VALOP(x)    \
    ((x) == '%' || isdigit(x) || (x) == '.' || (toupper(x) <= 'Z' && toupper(x) >= 'A'))

extern int        pfi_enabled;
extern uint32_t   pfi_address;
extern int        pfi_argstart;
extern FILE     * pfi_logfile;
extern int        pfi_append;
extern GMutex   * pfi_mutex;
extern int        pfi_logra;

static FILE * ra_log;

#undef SP
#undef S8

enum {
  R0, AT, V0, V1, A0, A1, A2, A3,
  T0, T1, T2, T3, T4, T5, T6, T7,
  S0, S1, S2, S3, S4, S5, S6, S7,
  T8, T9, K0, K1, GP, SP, S8, RA
};

static int
is_valid_f_char ( unsigned char j )
{
    static int gfdgdfg;
    static int g[256];
    
    if( !gfdgdfg )
    {
        g['d']=1;
        g['i']=1;
        g['o']=1;
        g['u']=1;
        g['x']=1;
        g['X']=1;
        g['e']=1;
        g['E']=1;
        g['f']=1;
        g['F']=1;
        g['g']=1;
        g['G']=1;
        g['c']=1;
        g['s']=1;
        g['p']=1;
        
        gfdgdfg = 1;
    }
    
    return g[j];
}

void
mem_get_str ( char * tgt, uint32_t addr )
{
    uint32_t w;
    char buff[512];
    int i, dp, b;
    int en[] = { 3, 2, 1, 0 };
    uint8_t * mem;
    
    mem = (uint8_t*)rdram;
    dp = 0;
    
    for( i = 0; i < sizeof(buff) - 1; i += 1 )
    {
        uint32_t next;
        uint32_t me;
        
        me = addr + i;
        
        /* Get the next character */
        next = mem[me - (me % 4) + en[me % 4]];
        
        /* Write */
        buff[dp++] = next;
        
        /* Finished? */
        if( !next )
        {
            /* yes */
            break;
        }
    }
    
    buff[sizeof(buff)-1] = '\0';
    
    strcpy( tgt, buff );
}

int
pfi_sprintf ( char * tgt, char * fmt, uint32_t * _stack )
{
    uint64_t data64;
    uint32_t data32;
    char spec[256], type;
    int i, d, f, len;
    uint32_t * sp;
    
    sp = _stack;
    
    for( i = 0, d = 0; fmt[i]; i++ )
    {
        #if 0
          if( d > 0 )
          {
              g_print( "%c", tgt[d-1] );
              g_usleep( G_USEC_PER_SEC / 2 );
          }
        #endif 
        
        /* Format specifier? */
        if( fmt[i] == '%' )
        {
            /* Just a percent...? */
            if( fmt[i+1] == '%' )
            {
                /* Copy & continue */
                tgt[d++] = '%';
                i += 2;
                continue;
            }
            
            /* Yes, grab it */
            for( f = 0; 
                fmt[i+f] && !isspace(fmt[i+f]); 
                f++ )
            {
                spec[f] = fmt[i+f];
                
                if( is_valid_f_char(fmt[i+f]) )
                {
                    f++;
                    break;
                }
            }
            spec[f] = '\0';
            
            #if 0
              g_print( "%s\n", spec );
              getchar();
            #endif
            
            /* Check type... */
            type = spec[f-1];
            
            /* How much data we need from stack */
            switch( type )
            {
                /* Eight bytes */
                case 'e': case 'E':
                case 'f': case 'F':
                case 'g': case 'G':
                   
                  len = 8;
                  
                break;
                
                /* Four bytes */
                case 'd': case 'i':
                case 'o': case 'u':
                case 'x': case 'X':
                  
                  /* 64-bit? */
                  if( spec[f-2] == 'l' && spec[f-3] == 'l' )
                    len = 8;
                  else
                    len = 4;
                
                break;
                
                default:
                  len = 4;
            }
            
            /* Grab the data... */
            if( len == 8 )
            {
                data64 = (uint64_t)*sp | (uint64_t)*(sp+1) << 32;
                sp += 2;
            }
            else
            {
                data32 = *sp++;
            }
            
            /* String? */
            if( type == 's' )
            {
                char str[512];
                
                /* Ok, grab it from memory */
                mem_get_str( str, data32 & MMASK );
                
                /* Go */
                d += sprintf( &tgt[d], spec, str );
            }
            else
            {
                if( len == 8 )
                {
                    d += sprintf( &tgt[d], spec, data64 );
                }
                else
                {
                    d += sprintf( &tgt[d], spec, data32 );
                }
            }
            
            /* Finished... */
            i += f - 1;
            continue;
        }
        
        /* No format -- straight copy */
        tgt[d++] = fmt[i];
    }
    
    /* NULL terminate */
    tgt[d] = '\0';
    
    return d;
}


void
pfi_do ( void )
{
    uint32_t fmtptr;
    uint32_t * sp;
    uint32_t stack[64];
    char format[512];
    char target[2048];
    int i;
    
    /* Place arguments on stack */
    stack[0] = (uint32_t)reg[A0];
    stack[1] = (uint32_t)reg[A1];
    stack[2] = (uint32_t)reg[A2];
    stack[3] = (uint32_t)reg[A3];
    
    /* Grab a few stack elements */
    sp = &rdram[((reg[SP] & MMASK) + 16) / 4];
    for( i = 4; i < sizeof(stack)/sizeof(uint32_t); i++ )
        stack[i] = *sp++;
    
    /* Get format string */
    fmtptr = (uint32_t)reg[A0 + pfi_argstart] & MMASK;
    mem_get_str( format, fmtptr );
    
    /* Doop doop. Log return address? */
    if( pfi_logra )
    {
        /* Need to open handle? */
        if( !ra_log )
        {
            /* Yep */
            ra_log = fopen( "ra_log.txt", "w" );
        }
        
        /* Write! */
        fprintf( ra_log, "[0x%08X]: %s", (uint32_t)reg[RA], format );
    }
    
    /* Preprae it */
    pfi_sprintf( target, format, stack + pfi_argstart + 1 );
    
    /* Write it to file */
    if( pfi_logfile )
        fprintf( pfi_logfile, "%s", target );
    
    /* g_print( "%s", target ); */
}

