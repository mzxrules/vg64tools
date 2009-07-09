#include <mips.h>
#include "../dodojr.h"

        .text

        /*
        *# Original address: 0x809f74c4
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f22
        .ent            En_Dodojr_f22

En_Dodojr_f22:        

        addiu   sp,sp,-48
        sw      s0,32(sp)
        move    s0,a0
        sw      ra,36(sp)
        sw      a1,52(sp)
        li      t6,100
        sw      t6,16(sp)
        move    a1,zero
        addiu   a0,a0,180
        li      a2,4
        jal     0x8007869c
        li      a3,1000
        lh      t7,180(s0)
        lui     at,0x4680
        mtc1    at,$f6
        mtc1    t7,$f4
        lui     at,0x4270
        mtc1    at,$f10
        cvt.s.w $f0,$f4
        lwc1    $f8,12(s0)
        move    a0,s0
        li      a2,3
        div.s   $f0,$f0,$f6
        mul.s   $f16,$f10,$f0
        add.s   $f18,$f8,$f16
        swc1    $f18,40(s0)
        swc1    $f0,44(sp)
        jal     0x809f6510
        lw      a1,52(sp)
        lwc1    $f0,44(sp)
        mtc1    zero,$f4
        lui     t8,0x8003
        addiu   t8,t8,-18964
        c.eq.s  $f0,$f4
        lui     at,0x809f
        bc1fl   0x809f757c
        lw      ra,36(sp)
        lh      t9,180(s0)
        sw      t8,192(s0)
        lui     t0,0x809f
        sh      t9,48(s0)
        lwc1    $f6,32652(at)
        addiu   t0,t0,30092
        sw      t0,400(s0)
        swc1    $f6,104(s0)
        lw      ra,36(sp)
        lw      s0,32(sp)
        addiu   sp,sp,48
        jr      ra
        nop
        
        .end            En_Dodojr_f22
        .set            at
        .set            reorder
