/* z_En_Bird.c
 spinout and ZZT32
*/

#include "../actor.h"

typedef unsigned int    u32;
typedef unsigned short  u16;
typedef unsigned char   u8;
typedef signed short    s16;
typedef float           f32;
typedef double          f64;

struct actor_spec_t
{
    0x0072,	/* Actor number */
    0x06,	/* Actor type */
    0x00,
    0x00000000,
    0x0077,	/* Object number */
    0x000001DC,	/* ??? */
    0x809C1BB8,	/* init */
    0x809C1CA0,	/* routine1 */
    0x809C1F5C,	/* routine2 */
    0x809C1F8C	/* routine3 */
};
    

void bird_func0x809C1BB0(struct z64_actor_t * a0, u32 * a1)
{
    a0->next_routine = a1;
}

void bird_func0x809C1BB8(struct z64_actor_t * a0, u32 * a1)
{
    _func0x800780DC(0, 0x809C1FF0);
    _func0x8002D62C(a0, 0x3C23D70A);
    _func0x800A457C(a0, a0 + 0x014C, 0x06002190, 0x0600006C, 0, 0); /* Animation init */
    _func0x8002B1E0(a0 + 0x00B4, 0x45ABE000, 0x8003B5EC);
      
    a0->_0x00AE = 0;
    a0->v0194 = 0;
    a0->v0198 = 0;
    a0->v01A0 = 0;
    a0->v01A4 = 0;
    a0->v01A8 = 1.5f;
    a0->v01AC = 0.5f;
    a0->v01B0 = 40.0f;
    a0->v01B8 = 0.0f;
    a0->v01BC = 70.0f;
    a0->v01C0 = 0x09C4;
    
    bird_func0x809C1CAC(a0, a0->variable); /* Local */
}

void bird_func0x809C1CA0(u32 * a0, u32 * a1)
    {
/* wtf?
sw	a0,0(sp)
jr	ra
sw	a1,4(sp)
*/
    }

void bird_func0x809C1CAC(struct z64_actor_t * a0, u32 * a1)
{
    u32 * v0;
    f32 * f0;

    *v0 = _func0x800A2000(0x0600006C);

    if (a0->v019C == 0)
    {
        *f0 = 0;
    }

    else
    {
        *f0 = 1.0;
    }

    _func0x80077D90(5, 35);
    _func0x800A51A0(a0 + 0x14C, 0x0600006C, *f0, 0.0, *v0, 0, 0.0);
    _func0x809C1BB0(a0, 0x809C1D60); /* Local */
}

void bird_func0x809C1D60(struct z64_actor_t * a0, u32 * a1)
{
    f32 * f0;
    
    *f0 = _func0x80100290(a0->v01B4);
    _func0x80078310(a0 + 0x68, 0.0, 0x3DCCCCCD, 0.5, 0.0);
    a0->_0x00BC = a0->_0x00BC+(a0->_0x01A0 * f0);

    if (a0->v019C == 0)
    {
        a0->v0168 = a0->_0x0068 + a0->_0x0068;
    }
    _func0x800A49FC(a0+0x14C);
    a0->v0198 -= 1;
    if (a0->v0198)
    {
        bird_func0x809C1E00(a0,a0->variable); /* Local jump. Second argument
                                                 is the actor variable */
    }
}

void bird_func0x809C1E00(void * a0, u32 * actor_var)
{
    _func0x80077D90(20, 45);
    bird_func0x809C1BB0(a0, 0x809C1E40);
}

void bird_func0x809C1E40(struct z64_actor_t * a0, u32 * a1)
{
    f32 * f0;
    int tmp;

    *f0 = _func0x80100290(a0->v01A4); /* This function might actually return two
                                         floats, but the function it is called by
                                         only appears to use two of them */
    a0->_0x00BC = a0->_0x00BC + (*f0 * a0->v01A0);
    _func0x80078310(a0+0x68, a0->v01A8, 0x3DCCCCCD, a0->v01AC, 0);
    *f0 =_func0x80078028(a0+0x24, a0+0x2C);
    
    if !(a0->v01B0 < *f0) && !(a0->v0198 < 4)
    {
        *f0 = _func0x80100290(a0, a1, a0->v01B4);
        tmp = *f0 * a0->v01A4;
        a0->y_rot_unknown_1 += tmp;
    }
    else
    {
        tmp = _func0x80078068(a0, a1)
        /*sll	a1,v0,0x10
          sra	a1,a1,0x10
          tmp <<= 16;
          tmp >>= 16; 
          Needed?*/
        _func0x8077B58(a0 + 0x32, tmp, a0->v01C0);
    }
    a0->_0x00B6 = a0->y_rot_unknown_1;
    _func0x800A49FC(a0+0x14C);
    a0->v0198 -= 1;
    if (a0->v0198 >= 0)
    {
        bird_func0x809C1CAC(a0, a0->variable)
    }
}

void bird_func0x809C1F5C(struct z64_actor_t * a0, a1)
{
    a0->v01B8 = a0->v01B8+a0->v01BC;
    goto a0->next_routine;
}

void bird_func0x809C1F8C( struct z64_actor_t * a, void * wut )
{
    _func0x800A15C8(
        wut,
        a->v0150,
        a->v016C,
        0
    );
}
