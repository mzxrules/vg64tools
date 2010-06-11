#include "bird.h"


void En_Bird_f2 ( struct z64_actor_t * a, u32 z_gp )
{    
    func_800780DC( a, En_Bird_dat1 );
    
    func_8002D62C( a, 0.01f );
    
    /* Animation init */
    func_800A457C(
        z_gp, 
        AADDR(a,0x014C), 
        0x06002190, 
        0x0600006C, 
        0, 
        0, 
        0
    ); 
    
    func_8002B1E0(
        AADDR(a,180), 
        0x45ABE000, 
        0x8002B5EC,
        0x40800000
    );
    
    AVAL(a,u8,174)  = 0;
    AVAL(a,u32,404) = 0;
    AVAL(a,u32,408) = 0;
    AVAL(a,u32,416) = 0;
    AVAL(a,u32,420) = 0;
    AVAL(a,f32,424) = 1.0f;
    AVAL(a,f32,428) = 0.5f;
    AVAL(a,f32,432) = 40.0f;
    
    AVAL(a,u32,440) = 0;
    AVAL(a,u32,444) = 70.0f;
    
    AVAL(a,u16,448) = 0x09C4;
    
    En_Bird_f4( 
        a, 
        a->variable 
    );
}

