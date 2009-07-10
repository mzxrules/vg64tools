#include "bird.h"


void En_Bird_f6(void * a0, u16 a1 )
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
