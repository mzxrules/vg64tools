#include <stdio.h>
#include "../mips.h"
#include "../actor.h"

extern void func_800a15c8 ( void *, u32, u32, u32 );


void
bird_ep ( void )
{
}


void
bird_last ( struct z64_actor_t * a, void * wut )
{
    func_800a15c8(
        wut,
        a->v0150,
        a->v016C,
        0
    );
}
