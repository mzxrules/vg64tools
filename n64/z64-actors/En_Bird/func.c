#include <mips.h>
#include <actor.h>
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
    AVAL(a0,u32,424) = 0x3FC00000;
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
/*
void En_Bird_f4 ( void * a0, void * a1 )
{
    f32 tmp;
    u32 v0;
    u32 f0; /* HACK- it should be a float, GCC shoots itself in the foot and does unessasry cop1 stuff*/
/*    struct z64_actor_t * a;
    
    a = (struct z64_actor_t*)a0;
    
    tmp = (f32)func_800A2000(0x0600006C);

    /* asm("mtc1 $v0, $f4\n"
	   "cvt.s.w $f4, $f6\n"
	   "swc1 $f6, 0x200($s0)"); */
/*
    if (AVAL(a0,u16,412) == 0)
    {
        f0 = 0;
    }

    else
    {
        f0 = 0x3F800000;
    }

    AVAL(a0,u32,408) = func_80077D90(
	5,
	35
    );

    func_800A51A0(
	AADDR(a0,0x14C),
	0x0600006C,
	f0,
	0,
	tmp, 
	0,
	0
    );
    
    En_Bird_f1(
	a0,
	En_Bird_f5
    );
}
*/
void En_Bird_f6(void * a0, void * a1 )
{
    struct z64_actor_t * a;
    a = (struct z64_actor_t*)a0;
    AVAL(a0, u32, 408) = func_80077D90(
 			20,
			45 );
    En_Bird_f1(
	a0,
	En_Bird_f7 );
}

void En_Bird_f8 ( void * a0, void * a1 )
{
    struct z64_actor_t * a;
    
    a = (struct z64_actor_t*)a0;
    
    AVAL(a0,f32,0x1B8) += AVAL(a0,f32,0x1BC);
    
    /* AVAL(a0,ZAFunc,400)( a0, a1); */
    a->f_next( a0, a1 );
}

void En_Bird_f9( void * a0, void * a1 )
{
    struct z64_actor_t * a;
    a = (struct z64_actor_t*)a0;

    func_800A15C8(
        a1,
        AVAL(a0,u32,336),
        AVAL(a0,u32,364),
        0,
        0,
        0
    );
}
