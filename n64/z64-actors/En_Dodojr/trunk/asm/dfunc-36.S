#include <mips.h>
#include "../dodojr.h"

        .text
        
        /*
        *# Original address: 0x809f7c90
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f36
        .ent            En_Dodojr_f36

En_Dodojr_f36:        

        addiu   sp,sp,-40
        sw      s0,32(sp)
        move    s0,a0
        sw      ra,36(sp)
        sw      a1,44(sp)
        jal     0x800a49fc
        addiu   a0,a0,332
        jal     0x8002d8e0
        move    a0,s0
        move    a0,s0
        jal     0x809f70e8
        lw      a1,44(sp)
        lw      v0,400(s0)
        lui     t6,0x809f
        addiu   t6,t6,29612
        beql    t6,v0,0x809f7d1c
        move    a0,s0
        lh      t7,468(s0)
        lh      t8,470(s0)
        mtc1    zero,$f8
        mtc1    t7,$f4
        mtc1    t8,$f6
        li      t9,5
        cvt.s.w $f4,$f4
        sw      t9,20(sp)
        lw      a0,44(sp)
        move    a1,s0
        swc1    $f8,16(sp)
        cvt.s.w $f6,$f6
        mfc1    a2,$f4
        mfc1    a3,$f6
        jal     0x8002e4b4
        nop
        lw      v0,400(s0)
        move    a0,s0
        jalr    v0
        lw      a1,44(sp)
        move    a0,s0
        jal     0x8002d5b8
        lui     a1,0x4120
        move    a0,s0
        jal     0x809f72a4
        lw      a1,44(sp)
        lw      ra,36(sp)
        lw      s0,32(sp)
        addiu   sp,sp,40
        jr      ra
        nop
        
        .end            En_Dodojr_f36
        .set            at
        .set            reorder
