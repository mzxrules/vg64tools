#include "../dodojr.h"


void 
En_Dodojr_f39 (void * a0, void * a1 )
{
    struct z64_actor_t * a;
    
    a = a0;
    
    if( a->f_next == En_Dodojr_f21 )
    {
        goto ret;
    }
    
    if( a->f_next == En_Dodojr_f34 )
    {
        goto ret;
    }
    
    func_80093D18(
        AVAL(a1,void*,0)
    );
    
    func_800A15C8(
        a1,
        AVAL(a,u32,336),
        AVAL(a,u32,364),
        En_Dodojr_f37,
        En_Dodojr_f38,
        a
    );
  
  ret:
  
    return;
}
