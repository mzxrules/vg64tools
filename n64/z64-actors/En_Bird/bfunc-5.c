#include "bird.h"


void En_Bird_f5( void * a0, void * a1 )
{
    struct z64_actor_t * a;
    a = (struct z64_actor_t*)a0;

    f32 f0;
    
    f0 = func_80100290(
        AVAL(a0,f32,0x1B4)
    );

    func_80078310(
        AADDR(a0, 0x68),
        0.0f,
        0.1f,
        0.5f,
        0.0f
    );

    AVAL(a0,f32,0x00BC) += AVAL(a0,f32,0x1A0) * f0;

    if( !AVAL(a0,u16,0x19C) )
    {
       AVAL(a0,f32,0x168) = AVAL(a0,f32,0x0068) * 2.0f;
    }

    func_800A49FC(
        AADDR(a0, 0x14C)
    );

    AVAL(a0,u32,0x198) -= 1;
    if (AVAL(a0,u32,0x198))
    {
        En_Bird_f6(
            a0,
            a->variable
        ); 
    }
}
