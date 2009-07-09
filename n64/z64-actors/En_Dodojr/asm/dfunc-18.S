#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f709c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f18
        .ent            En_Dodojr_f18

En_Dodojr_f18:        

        addiu	sp,sp,-24
        sw	ra,20(sp)
        sw	a0,24(sp)
        jal	0x8002f828
        li	a1,14369
        lw	a0,24(sp)
        li	at,-2
        lw	t6,4(a0)
        and	t7,t6,at
        jal	0x809f6a20
        sw	t7,4(a0)
        lw	a0,24(sp)
        lui	t8,0x809f
        addiu	t8,t8,31416
        sw	t8,400(a0)
        lw	ra,20(sp)
        addiu	sp,sp,24
        jr	ra
        nop
	
        .end            En_Dodojr_f18
        .set            at
        .set            reorder
