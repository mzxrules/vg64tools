#include "bird.h"

void En_Bird_f7( void * a0, void * a1 )
{
    struct z64_actor_t * a;
    a = (struct z64_actor_t*)a0;

    AVAL(a0,f32,0x00BC) += ( func_80100290( AVAL(a0,f32,0x1A4) ) * AVAL(a0,f32,0x1A0) );
				/* This ^ function might actually return two
                                   floats, but the function it is called by
                                   only appears to use two of them */

    func_80078310(a0+0x68, AVAL(a0,f32,0x1A8), 0.1f, AVAL(a0,f32,0x1AC), 0);
    /*
    if ((!( AVAL(a0,f32,0x01B0) < func_80078028( AADDR(a0,0x24), AADDR(a0,0x2C)))) && (!( AVAL(a0,u32,0x0198) < 4 )))
    {
        a -> rotation_2.y += ( func_80100290( AVAL(a0,f32,0x1B4) ) * AVAL(a0,f32,0x1A4) );
    }

    else
    {
        func_80077B58(a0 + 0x32, (u16)func_80078068(a0, a1), AVAL(a0,u16,0x1C0));
    }

    AVAL(a0,u16,0x00B6) = a -> rotation_2.y;
    
    if (AVAL(a0,u16,0x00B6) != 0)
    {
        AVAL(a0,u16,0x00B6) &= 0xFF00;
        AVAL(a0,u16,0x00B6) -= 0x0100;
    }
    */
    func_800A49FC(a0+0x14C);

    AVAL(a0,u32,0x0198) -= 1;

    if (AVAL(a0,u32,0x198) >= 0)
    {
        En_Bird_f4(
		a0,
		(void*)(int)a->variable);
    }
}
