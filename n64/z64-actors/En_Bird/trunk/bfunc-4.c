#include "bird.h"

void
En_Bird_f4 ( void * actor, void * u )
{
    float v, v2 = 0.0f;
    struct z64_actor_t * a;
    
    a = (struct z64_actor_t*)actor;
    
    
    v = (float)func_800A2000( 0x0600006C );
    
    if( !AVAL(a,s16,412) )
    {
        v2 = 1.0f;
    }
    
    AVAL(a,int,408) = func_80077D90( 5, 35 );
    
    func_800A51A0(
        AADDR(a,332),
        0x0600006C,
        v2,
        0.0f,
        v,
        0.0f,
        0.0f
    );
    
    En_Bird_f1( a, En_Bird_f5 );
}

