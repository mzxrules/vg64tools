#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f773c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f25
        .ent            En_Dodojr_f25

En_Dodojr_f25:        

        addiu   sp,sp,-24
        sw      ra,20(sp)
        sw      a1,28(sp)
        lh      v0,514(a0)
        bnez    v0,0x809f775c
        addiu   t6,v0,-1
        b       0x809f7764
        move    v1,zero
        sh      t6,514(a0)
        lh      v1,514(a0)
        bnezl   v1,0x809f77a0
        lw      ra,20(sp)
        jal     0x809f64d0
        sw      a0,24(sp)
        lw      a0,24(sp)
        li      $at,-2
        lw      t7,4(a0)
        and     t8,t7,$at
        jal     0x809f6a20
        sw      t8,4(a0)
        lw      a0,24(sp)
        lui     t9,0x809f
        addiu   t9,t9,30636
        sw      t9,400(a0)
        lw      ra,20(sp)
        addiu   sp,sp,24
        jr      ra
        nop
        
        .end            En_Dodojr_f25
        .set            at
        .set            reorder
