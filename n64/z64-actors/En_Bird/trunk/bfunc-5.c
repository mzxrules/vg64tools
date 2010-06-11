#include "bird.h"


void En_Bird_f5( struct z64_actor_t * a, u32 z_gp )
{
    f32 f0;
    
    f0 = sinf(AVAL(a,f32,0x1B4));

    func_80078310(
        AADDR(a, 0x68),
        0.0f,
        0.1f,
        0.5f,
        0.0f
    );

    AVAL(a,f32,0x00BC) += AVAL(a,f32,0x1a) * f0;

    if( !AVAL(a,u16,0x19C) )
    {
       AVAL(a,f32,0x168) = 0.5f;//AVAL(a,f32,0x0068) * 2.0f; animation speed
    }

    func_800A49FC(
        AADDR(a, 0x14C)
    );

    AVAL(a,u32,0x198) -= 1;
    if (AVAL(a,u32,0x198))
    {
        En_Bird_f6(
            a,
            a->variable
        ); 
    }
}
