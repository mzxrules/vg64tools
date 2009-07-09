#include "../dodojr.h"


void 
En_Dodojr_f36 (void * a0, void * a1 )
{
    struct z64_actor_t * a;
    
    a = a0;
    
    func_800A49FC(
        AADDR(a,332)
        /*
        *
        * Warning! This function may take another argument.
        *
        */
    );
    
    func_8002D8E0(
        a
    );
    
    En_Dodojr_f19(
        a,
        a1
    );
    
    if( a->f_next != En_Dodojr_f21 )
    {
        func_8002E4B4(
            a1,
            a,
            AVAL(a,s16,468), /* float */
            AVAL(a,s16,470), /* float */
            0.0f,
            5
        );
    }
    
    a->f_next( a, a1 );
    
    func_8002D5B8(
        a,
        10.0f
    );
    
    En_Dodojr_f20(
        a,
        a1
    );
}
