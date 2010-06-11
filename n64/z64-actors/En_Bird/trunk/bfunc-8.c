#include "bird.h"


void En_Bird_f8 ( struct z64_actor_t * a, ZAFunc function )
{    
    AVAL(a,f32,0x1B8) += AVAL(a,f32,0x1BC);
    
    a->f_next( a, function );
}
