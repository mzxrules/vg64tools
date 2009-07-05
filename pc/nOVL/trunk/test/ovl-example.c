#include <stdio.h>



char * fmt = "%s, %s! %i";
char * p1 = "Hello";
char * p2 = "world";

int array[40];

void
n64start ( void )
{
    extern void do_string ( void );
    
    do_string();
}

void
do_string ( void )
{
    kprintf( fmt, p1, p2, array[20] );
}



