#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f768c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f24
        .ent            En_Dodojr_f24

En_Dodojr_f24:        

        addiu   sp,sp,-24
        sw      ra,20(sp)
        sw      a1,28(sp)
        lwc1    $f4,356(a0)
        move    a2,a0
        li      a1,14416
        trunc.w.s       $f6,$f4
        mfc1    t7,$f6
        nop
        sll     t8,t7,0x10
        sra     t9,t8,0x10
        addiu   t0,t9,-8
        slti    $at,t0,4
        beqzl   $at,0x809f76fc
        move    a0,a2
        lw      v0,480(a0)
        lh      t1,504(v0)
        addiu   t2,t1,1
        sh      t2,504(v0)
        lw      t5,484(a0)
        lw      t3,480(a0)
        sw      t5,36(t3)
        lw      t4,488(a0)
        sw      t4,40(t3)
        lw      t5,492(a0)
        b       0x809f772c
        sw      t5,44(t3)
        move    a0,a2
        jal     0x8002f828
        sw      a2,24(sp)
        lw      a2,24(sp)
        jal     0x8002d570
        lw      a0,480(a2)
        lw      a2,24(sp)
        lui     t7,0x809f
        li      t6,24
        addiu   t7,t7,30524
        sh      t6,514(a2)
        sh      zero,508(a2)
        sw      t7,400(a2)
        lw      ra,20(sp)
        addiu   sp,sp,24
        jr      ra
        nop
        
        .end            En_Dodojr_f24
        .set            at
        .set            reorder
