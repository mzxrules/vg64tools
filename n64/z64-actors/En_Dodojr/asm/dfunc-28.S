#include <mips.h>
#include "../dodojr.h"

        .text
	
        /*
        *# Original address: 0x809f786c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f28
        .ent            En_Dodojr_f28

En_Dodojr_f28:        

        addiu	sp,sp,-40
        sw	ra,36(sp)
        sw	s0,32(sp)
        move	s0,a0
        jal	0x8002d868
        sw	a1,44(sp)
        move	a0,s0
        jal	0x809f68b0
        lw	a1,44(sp)
        beqzl	v0,0x809f78b0
        li	t7,10
        jal	0x809f6ac4
        move	a0,s0
        lui	t6,0x809f
        addiu	t6,t6,30956
        sw	t6,400(s0)
        li	t7,10
        sw	t7,16(sp)
        addiu	a0,s0,182
        move	a1,zero
        li	a2,4
        jal	0x8007869c
        li	a3,1000
        lh	t8,180(s0)
        lh	t9,510(s0)
        sh	t8,48(s0)
        sb	t9,276(s0)
        lw	ra,36(sp)
        lw	s0,32(sp)
        addiu	sp,sp,40
        jr	ra
        nop
	
        .end            En_Dodojr_f28
        .set            at
        .set            reorder
