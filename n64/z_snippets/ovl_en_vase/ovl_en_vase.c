#include "../mips.h"
#include "../actor.h"

extern void func_8002d62c ( struct z64_actor_t *, u32 );
extern void func_8002b1e0 ( void *, u32, void *, u32 );
extern void func_80035260 ( void *, u32 );

extern char obj_8002B5EC;

extern void vase_init ( struct z64_actor_t * a, void * o );
extern void vase_null ( struct z64_actor_t * a, void * o );
extern void vase_last ( struct z64_actor_t * a, void * o );


/* Create actor header */
MK_AHEAD
( 
    spec, 
    0x82, 
    6, 
    0,
    0x10,
    0x86,
    0x14C,
    
    vase_init, 
    vase_null, 
    (void*)0x80035118, 
    vase_last 
);


void
vase_init ( struct z64_actor_t * a, void * o )
{
    func_8002d62c( a, 0x3c23d70a );
    
    a->coords_3 = a->coords_2;
    
    func_8002b1e0( AADDR(a, 0x00B4), 0, &obj_8002B5EC, 0x40c00000 );
}

void
vase_null ( struct z64_actor_t * a, void * o )
{
    return;
}

void
vase_last ( struct z64_actor_t * a, void * o )
{
    func_80035260( o, 0x06000000 );
}

