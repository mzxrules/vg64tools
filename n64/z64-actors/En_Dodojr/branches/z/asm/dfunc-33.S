#include <mips.h>
#include "../dodojr.h"

        .text
        
        /*
        *# Original address: 0x809f7b3c
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f33
        .ent            En_Dodojr_f33

En_Dodojr_f33:        

        addiu   sp,sp,-56
        sw      ra,52(sp)
        sw      s0,48(sp)
        lh      v0,508(a0)
        move    s0,a0
        li      a2,16
        beqzl   v0,0x809f7b8c
        lwc1    $f4,40(s0)
        lbu     t6,276(a0)
        li      a1,16384
        li      a2,200
        bnez    t6,0x809f7bd0
        move    a3,zero
        jal     0x8003426c
        sw      v0,16(sp)
        lh      t7,508(s0)
        addiu   t8,t7,-1
        b       0x809f7bd0
        sh      t8,508(s0)
        lwc1    $f4,40(s0)
        lw      a3,36(s0)
        addiu   a0,a1,7204
        swc1    $f4,16(sp)
        lwc1    $f6,44(s0)
        sw      zero,36(sp)
        sw      zero,32(sp)
        sw      zero,28(sp)
        sw      zero,24(sp)
        jal     0x80031f50
        swc1    $f6,20(sp)
        beqz    v0,0x809f7bc0
        li      t9,8
        sh      zero,504(v0)
        lui     t0,0x809f
        addiu   t0,t0,31716
        sh      t9,514(s0)
        sw      t0,400(s0)
        lw      ra,52(sp)
        lw      s0,48(sp)
        addiu   sp,sp,56
        jr      ra
        nop
        
        .end            En_Dodojr_f33
        .set            at
        .set            reorder
