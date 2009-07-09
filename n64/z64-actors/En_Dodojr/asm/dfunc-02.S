#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f64a8
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f2
        .ent            En_Dodojr_f2

En_Dodojr_f2:        

        addiu	sp,sp,-24
        move	a2,a0
        sw	ra,20(sp)
        move	a0,a1
        jal	0x8005c3ac
        addiu	a1,a2,404
        lw	ra,20(sp)
        addiu	sp,sp,24
        jr	ra
        nop
        .end            En_Dodojr_f2
        .set            at
        .set            reorder

