#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f64d0
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f3
        .ent            En_Dodojr_f3

En_Dodojr_f3:        

        addiu   sp,sp,-32
        sw      ra,28(sp)
        sw      a0,32(sp)
        jal     0x8002f828
        li      a1,6158
        li      t6,8
        sw      t6,16(sp)
        lw      a0,32(sp)
        li      a1,16384
        li      a2,200
        jal     0x8003426c
        move    a3,zero
        lw      ra,28(sp)
        addiu   sp,sp,32
        jr      ra
        nop
        .end            En_Dodojr_f3
        .set            at
        .set            reorder

