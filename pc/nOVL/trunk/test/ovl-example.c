#include <stdio.h>
#include "mips.h"

extern void kprintf ( char * fmt, ... );

char * fmt = "%s, %s! 0x%08X";
char * p1 = "Hello";
char * p2 = "world";

void
ovlTest_main ( void )
{
    extern void do_string ( void );
    
    do_string();
}

void
do_string ( void )
{
    kprintf( fmt, p1, p2, (u32)ovlTest_main );
}



