#include "bird.h"


void En_Bird_f9( struct z64_actor_t * a, u32 z_gp )
{
    RenderFrame(
        z_gp,
        AVAL(a,u32,336),
        AVAL(a,u32,364),
        0,
        0,
        0
    );
}
