#include "bird.h"

f32 getz( f32 x, f32 radius)
{
    return _sqrt( _abs( (radius * radius) - (x * x) ) );
}

void En_Bird_f8 ( void * a0, void * a1 )
{
    f32 x_tmp = AVAL(a0,f32,0x80);
    f32 z_tmp = AVAL(a0,f32,0x84);
    f32 diff  = AVAL(a0,f32,0x64);
    u8 status = AVAL(a0,u8,3);

    struct z64_actor_t * a;
    
    a = (struct z64_actor_t*)a0;
    
    AVAL(a0,f32,0x1B8) += AVAL(a0,f32,0x1BC);
    
    AVAL(a0,u16,0x00B6) += 8;

    if (status & 1)
    {
        x_tmp += diff;
        if (x_tmp == 200.0f)
        {
            status &= 2;
        }
    }
    else
    {
        x_tmp -= diff;
        if (x_tmp == -200.0f)
        {
            status |= 1;
        }
    }

    z_tmp = getz( x_tmp, 200.0f );

    if (status & 2)
    {
        z_tmp = -z_tmp;
        if (z_tmp == -200.0f)
        {
            status &= 1;
        }
    }
    else
    {
        if (z_tmp == 200.0f)
        {
            status |= 2;
        }
    }

    AVAL(a0,f32,0x24) = AVAL(a0,f32,0x5C) + x_tmp;
    AVAL(a0,f32,0x80) = x_tmp;
    AVAL(a0,f32,0x2C) = AVAL(a0,f32,0x60) + z_tmp;
    AVAL(a0,f32,0x84) = z_tmp;
    AVAL(a0,u8,3) = status;

    /* AVAL(a0,ZAFunc,400)( a0, a1); */

    a->f_next( a0, a1 );
}
