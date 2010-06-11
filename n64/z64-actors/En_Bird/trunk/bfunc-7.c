#include "bird.h"

void En_Bird_f7( struct z64_actor_t * a, u32 z_gp )
{    
    AVAL(a,f32,188) += ( sinf( AVAL(a,f32,436) ) * AVAL(a,f32,416) );
    
    func_80078310(AADDR(a,104), AVAL(a,f32,424), 0.1f, AVAL(a,f32,428), 0.0f);
       
    f32 v = func_80078028(AADDR(a,36), AADDR(a, 8));
    
    if (AVAL(a,f32,432) < v || AVAL(a,u32,408) < 4)
    {
        func_80077B58(AADDR(a,50), (u16)func_80078068(AADDR(a,36), AADDR(a,8)), AVAL(a,u16,448));
    }
    
    else
    {
        a->rotation_2.y += (u32)( AVAL(a,f32,420) * sinf(AVAL(a,f32,436)) );
    }
    
    AVAL(a,u16,182) = a->rotation_2.y;
    
    func_800A49FC(AADDR(a,332));
    
    if(AVAL(a,u32,408)-- <= 0)
    {
        En_Bird_f4(a, a->variable);
    }
}
