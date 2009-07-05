#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


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

