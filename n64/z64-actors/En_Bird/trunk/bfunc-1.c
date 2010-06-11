#include "bird.h"


void SetNextFunction (struct z64_actor_t * a, ZAFunc next_func)
{
    a->f_next = next_func;
}
