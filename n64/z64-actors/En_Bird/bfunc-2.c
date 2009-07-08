#include "bird.h"


void En_Bird_f2 ( void * _a0, void * _a1 )
{
    struct z64_actor_old_t * a0;
    u32 * a1;
    
    a0 = (struct z64_actor_old_t*)_a0;
    a1 = (u32*)_a1;
    
    func_800780DC( a0, En_Bird_dat1 );
    
    func_8002D62C( a0, 0x3C23D70A );
    
    /* Animation init */
    func_800A457C(
        a1, 
        AADDR(a0,0x014C), 
        0x06002190, 
        0x0600006C, 
        0, 
        0, 
        0
    ); 
    
    func_8002B1E0(
        AADDR(a0,180), 
        0x45ABE000, 
        0x8002B5EC,
        0x40800000
    );
    
    AVAL(a0,u8,174)  = 0;
    AVAL(a0,u32,404) = 0;
    AVAL(a0,u32,408) = 0;
    AVAL(a0,u32,416) = 0;
    AVAL(a0,u32,420) = 0;
    AVAL(a0,float,424) = 0.5f; /* Animation speed */
    AVAL(a0,u32,428) = 0x3F000000;
    AVAL(a0,u32,432) = 0x42200000;
    
    AVAL(a0,u32,440) = 0;
    AVAL(a0,u32,444) = 0x428C0000;
    
    AVAL(a0,u16,448) = 0x09C4;
    
    En_Bird_f4( 
        a0, 
        (void*)(int)a0->variable 
    );
}

