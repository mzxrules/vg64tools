/*   \
:bird:
\   */

/* this code most likely will not compile */

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
    f32 * f12;
    
    f12 = (float*)(a0+0x1B4);
    *f0 = _func0x80100290(f12);
    _func0x80078310(a0 + 0x68, 0.0, 0x3DCCCCCD, 0.5, 0.0);
    a0->_0x00BC = a0->_0x00BC+(a0->_0x01A0 * f0);

    if (actw[0x19C/4] == 0)
    {
        actf[0x168/4] = actf[0x68/4] + actf[0x68/4];
    }
    _func0x800A49FC(a0+0x14C);
    actw[198/4] -= 1;
    if (actw[198/4])
    {
        bird_func0x809C1E00(a0,acth[0x1C/8]); /* Local jump. Second argument
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

    *f0 = _func0x80100290(a0->v01A4); /* This function might actually return two
                                         floats, but the function it is called by
                                         only appears to use two of them */
    actf[0xBC/4] = actf[0xBC/4] + (*f0 * a0->v01A0);
    _func0x80078310(a0+0x68, a0->v01A8, 0x3DCCCCCD, a0->v01AC, 0);
    _func0x80078028(a0+0x24, a0+0x2C);
    
    /* incomplete
addiu	sp,sp,-56
sw	ra,36(sp)
sw	s0,32(sp)
sw	a1,60(sp)
move	s0,a0
jal	0x80100290
lwc1	$f12,436(a0)
lwc1	$f6,416(s0)
lwc1	$f4,188(s0)
mtc1	zero,$f16
mul.s	$f8,$f0,$f6
lw	a1,424(s0)
lui	a2,0x3dcc
ori	a2,a2,0xcccd
addiu	a0,s0,104
add.s	$f10,$f4,$f8
swc1	$f10,188(s0)
jal	0x80078310
swc1	$f16,16(sp)
addiu	a0,s0,36
addiu	a1,s0,8
sw	a1,40(sp)
jal	0x80078028
sw	a0,44(sp)

I got to here <------------------

lwc1	$f18,432(s0)
lw	a0,44(sp)
lw	a1,40(sp)
c.lt.s	$f18,$f0
nop
bc1t	0x809c1ed0
nop
lw	t6,408(s0)
slti	at,t6,4
beqz	at,0x809c1ef4
nop
jal	0x80078068
nop
sll	a1,v0,0x10
sra	a1,a1,0x10
addiu	a0,s0,50
jal	0x80077b58
lh	a2,448(s0)
b	0x809c1f20
lh	t3,50(s0)
jal	0x80100290
lwc1	$f12,436(s0)
lwc1	$f6,420(s0)
lh	t7,50(s0)
mul.s	$f4,$f0,$f6
trunc.w.s	$f8,$f4
mfc1	t1,$f8
nop
addu	t2,t7,t1
sh	t2,50(s0)
lh	t3,50(s0)
addiu	a0,s0,332
jal	0x800a49fc
sh	t3,182(s0)
lw	t4,408(s0)
move	a0,s0
addiu	t5,t4,-1
bgez	t5,0x809c1f48
sw	t5,408(s0)
jal	0x809c1cac
lh	a1,28(s0)
lw	ra,36(sp)
lw	s0,32(sp)
addiu	sp,sp,56
jr	ra
nop
*/
}
void bird_func0x809C1F5C(a0, a1)
{
/*
addiu	sp,sp,-24
sw	ra,20(sp)
lwc1	$f4,436(a0)
lwc1	$f6,440(a0)
lw	t9,400(a0)
add.s	$f8,$f4,$f6
jalr	t9
swc1	$f8,436(a0)
lw	ra,20(sp)
addiu	sp,sp,24
jr	ra
nop
*/
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
