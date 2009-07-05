#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <glib.h>
#include "novl.h"
#include "mesg.h"

#ifdef NOVL_NO_COLORS
 char *
 mesg_strip_contro_characters ( char * str )
 {
     char * src, * tgt, * new;
     int c;
     
     src = str;
     tgt = (new = malloc( strlen(str) ));
     
     while( (c = *src) )
     {
         /* ANSI escape sequence? */
         if( c == ANSI_START[0] )
         {
             /* Yes, skip all characters in sequence */
             while( (*(src++) != 'm') );
             continue;
         }
         
         /* Regular characters */
         *(tgt++) = c;
         
         src++;
     }
     
     *tgt = '\0';
     
     return new;
 }
#endif


int
mk_mesg_f ( char * symbol, char * fmt, va_list ap )
{
    char * final, * new_format;
    int length;
    #ifdef NOVL_NO_COLORS
     char * stripped;
    #endif
    
    new_format = g_strdup_printf( "%s %s\n", symbol, fmt );
    final = g_strdup_vprintf( new_format, ap );
    length = strlen( final );
    
    #ifdef NOVL_NO_COLORS
     stripped = mesg_strip_contro_characters( final );
     fprintf( stderr, "%s", stripped );
     free( stripped );
    #else
     fprintf( stderr, "%s", final );
    #endif
    
    g_free( new_format );
    g_free( final );
    
    return length;
}

int
mk_mesg ( char * symbol, char * fmt, ... )
{
    va_list ap;
    int len;
    
    va_start( ap, fmt );
    len = mk_mesg_f( symbol, fmt, ap );
    va_end( ap );
    
    return len;
}


int
MESG ( char * fmt, ... )
{
    va_list ap;
    int len;
    
    va_start( ap, fmt );
    len = mk_mesg_f( "[" ANSI_SET_FG_BLUE "-" ANSI_RESET_DEFAULT "]", fmt, ap );
    va_end( ap );
    
    return len;
}


int
ERROR ( char * fmt, ... )
{
    va_list ap;
    int len;
    
    va_start( ap, fmt );
    len = mk_mesg_f( "[" ANSI_SET_FG_RED "!" ANSI_RESET_DEFAULT "]", fmt, ap );
    va_end( ap );
    
    return len;
}


#ifdef NOVL_DEBUG
 int
 DEBUG ( char * fmt, ... )
 {
    va_list ap;
    int len;
    
    va_start( ap, fmt );
    len = mk_mesg_f( "[" ANSI_SET_FG_GREEN "@" ANSI_RESET_DEFAULT "] ", fmt, ap );
    va_end( ap );
    
    return len;
 }


 int
 DEBUG_R ( char * fmt, ... )
 {
    va_list ap;
    int len;
    
    va_start( ap, fmt );
    len = mk_mesg_f( "[" ANSI_SET_FG_CYAN "*" ANSI_RESET_DEFAULT "] ", fmt, ap );
    va_end( ap );
    
    return len;
 }
#endif
