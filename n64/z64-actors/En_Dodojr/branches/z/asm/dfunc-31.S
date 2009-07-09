#include <mips.h>
#include "../dodojr.h"

        .text
        
        /*
        *# Original address: 0x809f7a00
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f31
        .ent            En_Dodojr_f31

En_Dodojr_f31:        

        addiu   sp,sp,-40
        sw      s0,32(sp)
        move    s0,a0
        sw      ra,36(sp)
        sw      a1,44(sp)
        li      t6,100
        sw      t6,16(sp)
        li      a1,16384
        addiu   a0,a0,180
        li      a2,4
        jal     0x8007869c
        li      a3,1000
        lh      v0,514(s0)
        li      t8,30
        bnez    v0,0x809f7a48
        addiu   t7,v0,-1
        b       0x809f7a54
        move    v1,zero
        sh      t7,514(s0)
        lh      v0,514(s0)
        move    v1,v0
        beqz    v1,0x809f7a8c
        subu    t9,t8,v0
        mtc1    t9,$f4
        lui     t,0x41f0
        mtc1    t,$f8
        cvt.s.w $f6,$f4
        lui     t,0x4270
        mtc1    t,$f16
        lwc1    $f10,12(s0)
        div.s   $f0,$f6,$f8
        mul.s   $f18,$f16,$f0
        sub.s   $f4,$f10,$f18
        b       0x809f7a94
        swc1    $f4,40(s0)
        jal     0x8002d570
        move    a0,s0
        move    a0,s0
        lw      a1,44(sp)
        jal     0x809f6510
        li      a2,3
        lw      ra,36(sp)
        lw      s0,32(sp)
        addiu   sp,sp,40
        jr      ra
        nop
        
        .end            En_Dodojr_f31
        .set            at
        .set            reorder

