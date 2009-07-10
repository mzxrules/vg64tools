#include "bird.h"


void En_Bird_f1 (void * a0, void * a1 )
{
    struct z64_actor_t * a;
    a = (struct z64_actor_t*)a0;
    AVAL(a0,u32,400) = (u32)a1;
}
