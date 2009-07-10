#include "bird.h"


void En_Bird_f8 ( void * a0, void * a1 )
{
    struct z64_actor_t * a;
    
    a = (struct z64_actor_t*)a0;
    
    AVAL(a0,f32,0x1B8) += AVAL(a0,f32,0x1BC);
    
    /* AVAL(a0,ZAFunc,400)( a0, a1); */
    a->f_next( a0, a1 );
}
