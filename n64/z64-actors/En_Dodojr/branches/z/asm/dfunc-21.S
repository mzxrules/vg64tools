#include <mips.h>
#include "../dodojr.h"

        .text

         /*
        *# Original address: 0x809f73ac
        */

        .set            noreorder
        .set            noat
        .global         En_Dodojr_f21
        .ent            En_Dodojr_f21

En_Dodojr_f21:        

        addiu   sp,sp,-48
        sw      s0,40(sp)
        move    s0,a0
        sw      ra,44(sp)
        lui     a0,0x600
        sw      a1,52(sp)
        jal     0x800a2000
        addiu   a0,a0,2144
        lui     $at,0x43a0
        mtc1    $at,$f8
        lwc1    $f6,144(s0)
        mtc1    v0,$f4
        lw      t6,52(sp)
        c.le.s  $f8,$f6
        cvt.s.w $f2,$f4
        lw      v1,7236(t6)
        bc1tl   0x809f74b4
        lw      ra,44(sp)
        lwc1    $f10,40(s0)
        lwc1    $f16,40(v1)
        lui     $at,0x4220
        mtc1    $at,$f18
        sub.s   $f0,$f10,$f16
        lui     a1,0x600
        lui     a2,0x3fe6
        ori     a2,a2,0x6666
        c.le.s  $f18,$f0
        addiu   a1,a1,2144
        addiu   a0,s0,332
        li      a3,0
        bc1t    0x809f74b0
        li      t7,1
        lui     $at,0xc120
        mtc1    $at,$f4
        swc1    $f2,16(sp)
        sw      t7,20(sp)
        jal     0x800a51a0
        swc1    $f4,24(sp)
        move    a0,s0
        jal     0x8002f828
        li      a1,14372
        lui     $at,0x4270
        mtc1    $at,$f8
        lwc1    $f6,40(s0)
        lh      t0,48(s0)
        lw      t4,36(s0)
        sub.s   $f10,$f6,$f8
        addiu   t1,t0,-16384
        lw      t8,4(s0)
        sh      t1,48(s0)
        swc1    $f10,40(s0)
        lw      t3,40(s0)
        sw      t4,496(s0)
        lh      t2,48(s0)
        lw      t4,44(s0)
        lwc1    $f16,128(s0)
        lui     t5,0x809f
        addiu   t5,t5,29892
        ori     t9,t8,0x1
        sw      t3,500(s0)
        sw      t9,4(s0)
        sw      t5,400(s0)
        sh      t2,180(s0)
        sw      t4,504(s0)
        swc1    $f16,500(s0)
        lw      ra,44(sp)
        lw      s0,40(sp)
        addiu   sp,sp,48
        jr      ra
        nop
        
        .end            En_Dodojr_f21
        .set            at
        .set            reorder
