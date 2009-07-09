#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f72a4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f20
        .ent            En_Dodojr_f20

En_Dodojr_f20:        

        addiu	sp,sp,-40
        sw	a1,44(sp)
        sw	ra,20(sp)
        addiu	a1,a0,404
        sw	a1,36(sp)
        jal	0x800626dc
        sw	a0,40(sp)
        lw	a3,40(sp)
        lui	t6,0x809f
        addiu	t6,t6,29612
        lw	v0,400(a3)
        lui	t7,0x809f
        addiu	t7,t7,31716
        beql	t6,v0,0x809f73a0
        lw	ra,20(sp)
        beq	t7,v0,0x809f739c
        lui	v1,0x809f
        addiu	v1,v1,29892
        beq	v1,v0,0x809f730c
        lui	t8,0x809f
        addiu	t8,t8,30092
        beq	t8,v0,0x809f730c
        lui	t9,0x809f
        addiu	t9,t9,31132
        bnel	t9,v0,0x809f733c
        lw	a0,44(sp)
        lw	a0,44(sp)
        lui	at,0x1
        ori	at,at,0x1e60
        lw	a2,36(sp)
        sw	v1,28(sp)
        sw	a3,40(sp)
        jal	0x8005d79c
        addu	a1,a0,at
        lw	a3,40(sp)
        lw	v1,28(sp)
        lw	v0,400(a3)
        lw	a0,44(sp)
        lui	at,0x1
        ori	at,at,0x1e60
        beq	v1,v0,0x809f7380
        addu	a1,a0,at
        lui	t0,0x809f
        addiu	t0,t0,30092
        beq	t0,v0,0x809f7380
        lui	t1,0x809f
        addiu	t1,t1,30828
        beq	t1,v0,0x809f7380
        lui	t2,0x809f
        addiu	t2,t2,30956
        beq	t2,v0,0x809f7380
        lui	t3,0x809f
        addiu	t3,t3,31132
        bne	t3,v0,0x809f7394
        nop
        lw	a2,36(sp)
        jal	0x8005d9f4
        sw	a1,24(sp)
        lw	a1,24(sp)
        lw	a0,44(sp)
        jal	0x8005dc4c
        lw	a2,36(sp)
        lw	ra,20(sp)
        addiu	sp,sp,40
        jr	ra
        nop
	
        .end            En_Dodojr_f20
        .set            at
        .set            reorder
