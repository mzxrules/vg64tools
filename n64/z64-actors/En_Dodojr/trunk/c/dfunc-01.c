#include "../dodojr.h"


void 
En_Dodojr_f1 (void * a0, void * a1 )
{
    struct z64_actor_t * a;
    int ret;
    
    a = a0;
    
    func_8002B1E0( 
        AADDR(a,180),
        0,
        0,
        18.0f /* <- shadow size */
    );
    
    func_800A457C(
        a1,
        AADDR(a,332),
        0x060020E0,
        0x060009D4,
        AADDR(a,524),
        AADDR(a,614),
        15
    );
    
    func_8005C364(
        a1,
        AADDR(a,404)
    );
    
    func_8005C4AC(
        a1,
        AADDR(a,404),
        a,
        __data_start + 32
    );
    
    ret = func_8005B200(
        4
    );
    
    func_80061EFC(
        AADDR(a,152),
        ret,
        __data_start + 76
    );
    
    AVAL(a,u8,279) = 14;
    AVAL(a,u32,4) &= (u32)(-2);
    
    func_8002D62C(
        a,
        0.02f  /* <- scale; rounded up to nearest 100th */
    );
    
    a->f_next = En_Dodojr_f21;
}
