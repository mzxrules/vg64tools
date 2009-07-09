#include <mips.h>
#include "../dodojr.h"

        .text
	
        /*
        *# Original address: 0x809f7d50
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f37
        .ent            En_Dodojr_f37

En_Dodojr_f37:        

        addiu	sp,sp,-48
        lui	t7,0x809f
        sw	ra,20(sp)
        sw	a0,48(sp)
        sw	a2,56(sp)
        sw	a3,60(sp)
        addiu	t7,t7,32612
        lw	t9,0(t7)
        addiu	t6,sp,32
        lw	t8,4(t7)
        sw	t9,0(t6)
        lw	t9,8(t7)
        li	at,1
        sw	t8,4(t6)
        bne	a1,at,0x809f7dcc
        sw	t9,8(t6)
        lw	t0,68(sp)
        lui	at,0x3f80
        mtc1	at,$f2
        lui	at,0x3f00
        mtc1	at,$f4
        lwc1	$f0,520(t0)
        sw	a1,52(sp)
        li	a3,1
        mul.s	$f6,$f0,$f4
        add.s	$f14,$f0,$f2
        add.s	$f12,$f6,$f2
        mfc1	a2,$f12
        jal	0x800d0a8c
        nop
        lw	a1,52(sp)
        li	at,4
        bnel	a1,at,0x809f7dec
        lw	ra,20(sp)
        lw	a1,68(sp)
        addiu	a0,sp,32
        jal	0x800d1af4
        addiu	a1,a1,484
        lw	ra,20(sp)
        addiu	sp,sp,48
        move	v0,zero
        jr	ra
        nop
	
        .end            En_Dodojr_f37
        .set            at
        .set            reorder
