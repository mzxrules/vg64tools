#include "bird.h"


void En_Bird_f6(struct z64_actor_t * a, u16 variable )
{
    AVAL(a, u32, 408) = func_80077D90(
 			20,
			45 );
    SetNextFunction(a, (ZAFunc)En_Bird_f7 );
}
